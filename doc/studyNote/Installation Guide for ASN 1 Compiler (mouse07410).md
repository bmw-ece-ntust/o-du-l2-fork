# Installation Guide for ASN.1 Compiler (mouse07410)

Start Date: 2025/01/17
Summary: Installation guide for the ASN.1 Compiler with detailed steps and verification methods.
Status: Done
Assign: Ming 咚咚 [銘鴻]
Tags: PIN
Finish Date: 2025/02/11
SUM: 🗓️ Days Spent to Complete: 25

## Prerequisites

[https://github.com/mouse07410/asn1c](https://github.com/mouse07410/asn1c)

Before starting the installation, ensure you have the necessary build tools installed on your system.

## Installation Steps

1. Clone the repository:
    
    ```bash
    GIT_SSL_NO_VERIFY=true git clone https://gitlab.eurecom.fr/oai/asn1c.git /tmp/asn1c
    # or
    git clone https://github.com/mouse07410/asn1c /tmp/asn1c
    ```
    
2. Navigate to the directory:
    
    ```bash
    cd /tmp/asn1c
    ```
    
3. Checkout the correct branch:
    
    ```bash
    git checkout vlm_master
    ```
    
4. Verify the version:
    
    ```bash
    git log -n1
    ```
    
5. Generate configuration files:
    
    ```bash
    autoreconf -iv
    ```
    
6. Configure the installation:
    
    ```bash
    ./configure --prefix /opt/asn1c/
    ```
    
7. Build the software:
    
    ```bash
    make -j`nproc`
    ```
    
8. Install the software (with sudo if needed):
    
    ```bash
    sudo make install
    ```
    

## Verification

After installation, verify that the compiler is properly installed by checking its version:

```bash
asn1c -version
```

<aside>
Note: If you encounter any permission issues during installation, ensure you have the necessary sudo privileges.

</aside>

## Successful Installation Check

After installation, you can verify the full functionality by running the help command:

```bash
/opt/asn1c/bin/asn1c --help
```

You should see detailed output showing all available compiler options including:

- Basic options like -E (parser only) and -P (print compiled text)
- Directory options (-S for support files, -D for destination)
- Debug options (-Wdebug-*)
- Various feature flags (-f* options)
- Encoding rule options (BER, XER, JER, OER, etc.)

<aside>
The default support files directory is set to "/opt/asn1c/share/asn1c". Make sure this path exists and contains the necessary skeleton files.

</aside>

```bash
ASN.1 Compiler, v0.9.29
Copyright (c) 2003-2017 Lev Walkin <vlm@lionet.info> and contributors.
Usage: asn1c [options] file ...
Options:
  -E                    Run only the ASN.1 parser and print out the tree
  -F                    During -E operation, also perform tree fixing

  -P                    Concatenate and print the compiled text
  -R                    Restrict output (tables only, no support code)
  -S <dir>              Directory with support (skeleton?) files
                        (Default is "/opt/asn1c/share/asn1c")
  -D <dir>              Destination directory for generated files (default current dir)
  -X                    Generate and print the XML DTD

  -Werror               Treat warnings as errors; abort if any warning
  -Wdebug-lexer         Enable verbose debugging output from lexer
  -Wdebug-parser        Enable verbose debugging output from parser
  -Wdebug-fixer         --//-- semantics processor
  -Wdebug-compiler      --//-- compiler

  -fbless-SIZE          Allow SIZE() constraint for INTEGER etc (non-std.)
  -fcompound-names      Disambiguate C's struct NAME's inside top-level types
  -findirect-choice     Compile members of CHOICE as indirect pointers
  -fincludes-quoted     Generate #includes in "double" instead of <angle> quotes
  -fknown-extern-type=<name>    Pretend the specified type is known
  -fline-refs           Include ASN.1 module's line numbers in comments
  -fno-constraints      Do not generate the constraint checking code
  -fno-include-deps     Do not generate the courtesy #includes for dependencies
  -funnamed-unions      Enable unnamed unions in structures
  -fwide-types          Use INTEGER_t instead of "long" by default, etc.
  -fprefix=<prefix>     Add the specified prefix to generated types

  -no-gen-BER           Do not generate the Basic Encoding Rules (BER, X.690) support code
  -no-gen-XER           Do not generate the XML Encoding Rules (XER, X.693) support code
  -no-gen-JER           Do not generate the JSON Encoding Rules (JER, X.697) support code
  -no-gen-OER           Do not generate the Octet Encoding Rules (OER, X.696) support code
  -no-gen-UPER          Do not generate the Unaligned Packed Encoding Rules (PER, X.691) support code
  -no-gen-APER          Do not generate the Aligned Packed Encoding Rules (PER, X.691) support code
  -no-gen-print         Do not generate the print code
  -no-gen-random-fill   Do not generate the random fill code
  -no-gen-example       Do not generate the ASN.1 format converter example
  -gen-autotools        Generate example top-level configure.ac and Makefile.am
  -pdu={all|auto|Type}  Generate PDU table (discover PDUs automatically)

  -print-class-matrix   Print out the collected object class matrix (debug)
  -print-constraints    Explain subtype constraints (debug)
  -print-lines          Generate "-- #line" comments in -E output
```