# Modify OSC SIB1 same as OAI SIB1

Start Date: 2024/06/14
Summary: Modify OSC SIB1 parameters to align with OAI SIB1 specifications.
Status: Done
Assign: Ming 咚咚 [銘鴻]

## Outcome

[https://www.diffchecker.com/uPwtKEgM/](https://www.diffchecker.com/uPwtKEgM/)

## First step:

Modify OSC parameters to match OAI parameters

(based on SIB1 print XML Log)

## Second step:

Add all values present in OAI but missing in OSC

(based on SIB1 print XML Log)

## Third step:

Delete all values present in OSC but missing in OAI

(based on SIB1 print XML Log)

→ Currently, it is still not possible to decode SIB1 through native OSC. It can only be achieved by forcibly hardcoding the TX_Data value within the unpack function to send out RA.