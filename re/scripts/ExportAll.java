// Ghidra headless post-script: dumps decompiled C, function list, strings and
// call graph of the current program into re/out/<PROGRAM>/.
//@category Export

import ghidra.app.script.GhidraScript;
import ghidra.app.decompiler.*;
import ghidra.program.model.listing.*;
import ghidra.program.model.address.*;
import ghidra.program.model.symbol.*;
import ghidra.program.model.data.*;
import ghidra.program.util.DefinedStringIterator;
import java.io.*;
import java.util.*;

public class ExportAll extends GhidraScript {
    @Override
    public void run() throws Exception {
        String[] args = getScriptArgs();
        File outRoot = new File(args.length > 0 ? args[0] : "out");
        String name = currentProgram.getName().replaceAll("\\.[Ee][Xx][Ee]$", "");
        File dir = new File(outRoot, name);
        dir.mkdirs();

        Listing listing = currentProgram.getListing();
        FunctionManager fm = currentProgram.getFunctionManager();

        // strings
        try (PrintWriter pw = new PrintWriter(new FileWriter(new File(dir, "strings.txt")))) {
            for (Data d : DefinedStringIterator.forProgram(currentProgram)) {
                Object v = d.getValue();
                if (v == null) continue;
                StringBuilder refs = new StringBuilder();
                for (Reference r : getReferencesTo(d.getAddress())) {
                    Function f = fm.getFunctionContaining(r.getFromAddress());
                    refs.append(' ').append(f != null ? f.getName() : r.getFromAddress().toString());
                }
                pw.printf("%s\t%s\t[%s ]%n", d.getAddress(),
                    v.toString().replace("\n", "\\n").replace("\t", "\\t"), refs);
            }
        }

        // function list + call graph
        try (PrintWriter pw = new PrintWriter(new FileWriter(new File(dir, "functions.txt")))) {
            for (Function f : fm.getFunctions(true)) {
                StringBuilder calls = new StringBuilder();
                for (Function c : f.getCalledFunctions(monitor)) calls.append(' ').append(c.getName());
                StringBuilder callers = new StringBuilder();
                for (Function c : f.getCallingFunctions(monitor)) callers.append(' ').append(c.getName());
                pw.printf("%s\t%s\tsize=%d\tcalls:%s\tcallers:%s%n", f.getEntryPoint(), f.getName(),
                    f.getBody().getNumAddresses(), calls, callers);
            }
        }

        // decompile everything
        DecompInterface di = new DecompInterface();
        DecompileOptions opts = new DecompileOptions();
        di.setOptions(opts);
        di.toggleCCode(true);
        di.toggleSyntaxTree(true);
        di.setSimplificationStyle("decompile");
        di.openProgram(currentProgram);
        try (PrintWriter pw = new PrintWriter(new FileWriter(new File(dir, "decomp.c")))) {
            for (Function f : fm.getFunctions(true)) {
                if (monitor.isCancelled()) break;
                DecompileResults res = di.decompileFunction(f, 120, monitor);
                pw.printf("/* ==== %s @ %s ==== */%n", f.getName(), f.getEntryPoint());
                if (res != null && res.decompileCompleted())
                    pw.println(res.getDecompiledFunction().getC());
                else
                    pw.println("/* decompile failed: " + (res == null ? "null" : res.getErrorMessage()) + " */\n");
            }
        }
        di.dispose();
        println("Exported " + name + " to " + dir.getAbsolutePath());
    }
}
