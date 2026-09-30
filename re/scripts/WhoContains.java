// prints the function containing each address given as script argument
//@category Export
import ghidra.app.script.GhidraScript;
import ghidra.program.model.listing.*;
public class WhoContains extends GhidraScript {
    public void run() throws Exception {
        for (String s : getScriptArgs()) {
            Function f = currentProgram.getFunctionManager().getFunctionContaining(toAddr(Long.parseLong(s, 16)));
            println("WHO " + s + " -> " + (f == null ? "none" : f.getEntryPoint() + " " + f.getName() + " " + f.getBody()));
        }
    }
}
