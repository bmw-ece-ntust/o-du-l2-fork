# OSC asn1c .cmake File Generation

Start Date: 2024/11/29
Summary: Generating .cmake files for the ASN.1c component of the OSC project based on predefined action items.
Status: padding
Assign: Ming 咚咚 [銘鴻]

<aside>

Following Robert's technique on setting up CMake for ASN.1, I am eager to delve deeper into this area and attempt to apply it specifically to the ASN.1c component of the OSC project.

</aside>

### About the .cmake File Generation

The `.cmake` file serves as a configuration file that specifies:

- The base grammar `.asn` file
- Generated output files (headers and source files)

This configuration enables parallel building of multiple ASN.1 components including:

- Protocol implementations:
    - S1AP, NGAP, F1AP, E1AP
    - X2AP, XnAP, M2AP, M3AP
    - LTE RRC, NR RRC
    - NRPPA, LPP

The file creation process is manual but straightforward:

1. Create initial `.asn1` file with basic settings:
`set(grammar <file>)
set(source ...)
set(header ...)`
2. Run `asn1c` to generate files in a subdirectory
3. Add generated filenames using either:
    - Vim command: `:read ls <dir>/*.h`
    - Bash command: `ls <dir>/*.h >> nr-rrc-17.3.0.cmake`
4. Rearrange the content as needed

Here are the action items for .cmake file generation:

1. Create initial .asn1 file with basic settings, including grammar, source, and header specifications
2. Run asn1c to generate files in a subdirectory
3. Add generated filenames using one of these methods:
    - Use Vim command: :read ls <dir>/*.h
    - Or use Bash command: ls <dir>/*.h >> nr-rrc-17.3.0.cmake
4. Rearrange the content as needed