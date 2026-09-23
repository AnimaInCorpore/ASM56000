// For every cdecl call whose caller pops more stack bytes (add esp,N after the
// call) than the callee's signature accounts for, record a call-site prototype
// override with N/4 parameters.  This makes the decompiler show the arguments
// of printf-style calls (CRT and Motorola's own error(fmt, ...) helpers).
//@category Export

import ghidra.app.script.GhidraScript;
import ghidra.program.model.address.Address;
import ghidra.program.model.data.*;
import ghidra.program.model.listing.*;
import ghidra.program.model.pcode.HighFunctionDBUtil;
import ghidra.program.model.scalar.Scalar;
import ghidra.program.model.symbol.*;

public class FixVarargCalls extends GhidraScript {
    @Override
    public void run() throws Exception {
        Listing listing = currentProgram.getListing();
        FunctionManager fm = currentProgram.getFunctionManager();
        int fixed = 0;
        InstructionIterator it = listing.getInstructions(true);
        while (it.hasNext() && !monitor.isCancelled()) {
            Instruction ins = it.next();
            if (!ins.getFlowType().isCall()) continue;
            Address[] flows = ins.getFlows();
            if (flows.length != 1) continue;
            Function callee = fm.getFunctionAt(flows[0]);
            if (callee == null) continue;
            if (callee.isThunk()) callee = callee.getThunkedFunction(true);
            Function caller = fm.getFunctionContaining(ins.getAddress());
            if (caller == null) continue;
            Instruction nxt = ins.getNext();
            if (nxt == null || !nxt.getMnemonicString().equals("ADD")) continue;
            if (!nxt.getDefaultOperandRepresentation(0).equals("ESP")) continue;
            Object[] o = nxt.getOpObjects(1);
            if (o.length != 1 || !(o[0] instanceof Scalar)) continue;
            int nargs = (int) (((Scalar) o[0]).getUnsignedValue() / 4);
            int have = callee.getParameterCount();
            if (nargs <= have || nargs > 24) continue;
            FunctionDefinitionDataType sig = new FunctionDefinitionDataType(callee, true);
            ParameterDefinition[] old = sig.getArguments();
            ParameterDefinition[] params = new ParameterDefinition[nargs];
            for (int i = 0; i < nargs; i++) {
                if (i < old.length) params[i] = old[i];
                else params[i] = new ParameterDefinitionImpl("va" + (i - old.length),
                        Undefined4DataType.dataType, null);
            }
            sig.setArguments(params);
            sig.setVarArgs(false);
            try {
                HighFunctionDBUtil.writeOverride(caller, ins.getAddress(), sig);
                fixed++;
            } catch (Exception e) {
                println("override failed at " + ins.getAddress() + ": " + e.getMessage());
            }
        }
        println("call-site overrides written: " + fixed);
    }
}
