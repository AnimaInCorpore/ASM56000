// Creates functions at addresses listed in a file (one hex address per line) -
// code that is reachable only through data tables - then also at every call
// target found in the newly disassembled code that has no function yet.
// usage: -postScript CreateHidden.java <address-list-file>
//@category Export

import ghidra.app.script.GhidraScript;
import ghidra.program.model.address.Address;
import ghidra.program.model.listing.*;
import java.io.*;
import java.nio.file.*;
import java.util.*;

public class CreateHidden extends GhidraScript {
    @Override
    public void run() throws Exception {
        String[] args = getScriptArgs();
        FunctionManager fm = currentProgram.getFunctionManager();
        Listing listing = currentProgram.getListing();
        Deque<Address> todo = new ArrayDeque<>();
        for (String line : Files.readAllLines(new File(args[0]).toPath())) {
            line = line.trim();
            if (line.isEmpty() || line.startsWith("#")) continue;
            todo.add(toAddr(Long.parseLong(line, 16)));
        }
        int made = 0, extra = 0;
        Set<Address> seen = new HashSet<>();
        while (!todo.isEmpty()) {
            Address a = todo.poll();
            if (!seen.add(a)) continue;
            if (fm.getFunctionAt(a) != null) continue;
            if (fm.getFunctionContaining(a) != null) continue;
            disassemble(a);
            Function f = createFunction(a, null);
            if (f == null) { println("cannot create function at " + a); continue; }
            made++;
            InstructionIterator it = listing.getInstructions(f.getBody(), true);
            while (it.hasNext()) {
                Instruction ins = it.next();
                if (!ins.getFlowType().isCall()) continue;
                for (Address t : ins.getFlows()) {
                    if (fm.getFunctionAt(t) == null && t.getOffset() < 0x483400L) { todo.add(t); extra++; }
                }
            }
        }
        println("created " + made + " functions (" + extra + " call targets queued)");
    }
}
