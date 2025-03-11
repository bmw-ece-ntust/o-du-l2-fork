# Try using backtrace in OAI UE(Segmentation fault)

Start Date: 2024/11/01
Summary: Debugging and addressing a segmentation fault in the nr_update_sr function caused by a null pointer dereference of pucch_Config.
Status: Done
Assign: Ming 咚咚 [銘鴻]
Finish Date: 2024/11/01
SUM: 🗓️ Days Spent to Complete: 0

<aside>
💡

Issues: [UE Segmentation fault after Generating RRCSetupComplete](UE%20Segmentation%20fault%20after%20Generating%20RRCSetupCom%2012110098314381d1adf3f719885a3bf8.md) 

</aside>

The segmentation fault occurs in the `nr_update_sr` function due to a null pointer dereference of `pucch_Config`, indicating potential initialization issues or memory management errors.

### Detailed Notes

1. **Error Context**:
    - The error is encountered in the function `nr_update_sr` at line 1184, specifically during the call to `check_pucchres_for_pending_SR`.
2. **Primary Issue**:
    - The variable `pucch_Config` is found to be `NULL`, leading to a segmentation fault when dereferenced.
3. **Potential Causes**:
    - **Uninitialized Pointer**: `pucch_Config` may not have been initialized properly before its use.
    - **Memory Management Errors**: There could be issues in memory allocation or assignment for `mac` or related structures.
    - **Race Conditions**: If this code is executed in a multithreaded environment, it could be affected by race conditions leading to inconsistent state.
4. **Proposed Solutions**:
    - **Null Check**: Implement a check for `pucch_Config` before dereferencing it to prevent the segmentation fault.
    - **Initialization Verification**: Ensure that all pointers and structures are properly initialized before use.
    - **Synchronization**: If applicable, use mutexes or other synchronization mechanisms to protect access to shared data in a multithreaded context.
    - **Function Logic Review**: Examine the logic within `check_pucchres_for_pending_SR` to ensure it handles null values appropriately.
5. **Debugging Steps**:
    - Add logging in `nr_update_sr` to output the values of `pucch_Config` and `lc_info` for debugging purposes.
    - Set a watchpoint in GDB to monitor changes to the relevant fields in the `mac` structure during execution.

[In Chinese](In%20Chinese%201311009831438093b758e04626cb47e4.md)