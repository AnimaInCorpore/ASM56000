// Applies names and prototypes from re/crt/<PROGRAM>.names.txt (and optional
// re/names/<PROGRAM>.names.txt for user code) to the current program.
// Line format: addr<TAB>F|D<TAB>name<TAB>prototype-or-type<TAB>...
//@category Export

import ghidra.app.script.GhidraScript;
import ghidra.app.util.cparser.C.CParserUtils;
import ghidra.app.cmd.function.ApplyFunctionSignatureCmd;
import ghidra.program.model.address.Address;
import ghidra.program.model.data.*;
import ghidra.program.model.listing.*;
import ghidra.program.model.symbol.SourceType;
import java.io.*;
import java.nio.file.*;

public class ApplyNames extends GhidraScript {
    @Override
    public void run() throws Exception {
        String[] args = getScriptArgs();
        File root = new File(args.length > 0 ? args[0] : ".");
        String prog = currentProgram.getName().replaceAll("\\.[Ee][Xx][Ee]$", "");
        for (String sub : new String[] { "crt", "names" }) {
            File f = new File(new File(root, sub), prog + ".names.txt");
            if (f.exists()) apply(f);
        }
    }

    private void apply(File f) throws Exception {
        int nf = 0, np = 0, nd = 0;
        for (String line : Files.readAllLines(f.toPath())) {
            if (line.startsWith("#") || line.isBlank()) continue;
            String[] p = line.split("\t", -1);
            if (p.length < 3) continue;
            Address a = toAddr(Long.parseLong(p[0], 16));
            String name = p[2].trim();
            String type = p.length > 3 ? p[3].trim() : "";
            if (p[1].equals("F")) {
                Function fn = getFunctionAt(a);
                if (fn == null) { disassemble(a); fn = createFunction(a, name); }
                if (fn == null) { println("no function at " + a); continue; }
                fn.setName(name, SourceType.USER_DEFINED);
                nf++;
                if (!type.isEmpty()) {
                    try {
                        FunctionDefinitionDataType sig = CParserUtils.parseSignature(
                            (ghidra.app.services.DataTypeManagerService) null, currentProgram, type, true);
                        if (sig != null) {
                            new ApplyFunctionSignatureCmd(a, sig, SourceType.USER_DEFINED)
                                .applyTo(currentProgram, monitor);
                            np++;
                        }
                    } catch (Exception e) {
                        println("bad prototype @" + a + ": " + type + " (" + e.getMessage() + ")");
                    }
                }
            } else if (p[1].equals("D")) {
                createLabel(a, name, true, SourceType.USER_DEFINED);
                nd++;
            }
        }
        println(f.getName() + ": " + nf + " functions (" + np + " prototypes), " + nd + " data labels");
    }
}
