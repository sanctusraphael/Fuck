# Fuck - The Fucking Language
Version 1.0.0  
Latest revision date: November 24th 2015  
by Ricardo Bastos



## Contents

<ul>
<li>1. Description</li>
<li>2. Keywords</li>
<li>3. Multi-line Statements</li>
<ul>
<li>3.1 Repetition</li>
<li>3.2 Variation</li>
<li>3.3 Supplementary Statements</li>
<li>3.4 Stacking</li>
</ul>
<li>4. Storage</li>
<li>5. Output</li>
<li>6. Validation Procedures</li>
<ul>
<li>6.1 Non-multi-line Statements</li>
<ul>
<li>6.1.1 First Keyword</li>
<li>6.1.2 Second Keyword</li>
<li>6.1.3 Last Keywords</li>
<li>6.1.4 Single Keywords in a Line</li>
</ul>
<li>6.2 Multi-line Statements</li>
<li>6.3 Supplementary Statements</li>
<li>6.4 Other Important Rules</li>
</ul>
<li>Annex A (informative) The C Fuck Interpreter</li>
<ul>
<li>A.1 Input Parameters</li>
<ul>
<li>A.1.1 Interactive Mode</li>
<li>A.1.2 Read File Mode</li>
<li>A.1.3 Multi-line Indentation Spaces</li>
</ul>
<li>A.2 Error Handling</li>
</ul>
<li>Annex B (informative) Fuck Vim Syntax Files</li>
</ul>



## 1. Description

**Fuck** is **The Fucking Language**. This fucking thing fucking does some goddamn motherfucking things. Fuckers won't even notice. Motherfuckers won't bat an eye. In case it fucks? Well, fuck! It's fucked!



## 2. Keywords

    fuck - Output to console
    fucked - Storage assignment operator
    fucker - Constant binary number 0
    motherfucker - Constant binary number 1
    fucking - Duplicate value
    motherfucking - Quadriplicate value
    fuckers - Storage 1 (Defaulted to binary number 0)
    motherfuckers - Storage 2 (Defaulted to binary number 0)



## 3. Multi-line Statements

*"fucking"* and *"motherfucking"* duplicate and quadriplicate, respectively, the value represented by *"fucker"*, *"motherfucker"*, *"fuckers"* or *"motherfuckers"*. After a *"fucking"* or *"motherfucking"* keyword, the values that should be affected should be put in a new line (the current and subsequent lines will be part of a **multi-line statement**). If desired, in Read File Mode, the new line in the file may be indented by spaces or tabs for organizational purposes. Some of the possible statements are:

    fucking
      fucker => 00
    fucking
      motherfucker => 11
    motherfucking
      fucker => 0000
    motherfucking
      motherfucker => 1111
    
The new line may also have *"fucking"* or *"motherfucking"* keywords, making the next line be included in the whole multi-line statement. Lines in multi-line statements must not be empty (contain only a single newline character, spaces or tabs).


### 3.1 Repetition

Usage of *"fucking"* and *"motherfucking"* may be repeated in the same line. For example:

    fucking motherfucking
      fucker => 00000000 (2 times 4)
    motherfucking motherfucking
      motherfucker => 1111111111111111 (4 times 4)


### 3.2 Variation

Variation is possible:

    fucker motherfucker => 01
    motherfucker fucker => 10
    fucking
      fucker motherfucker => 0101
    motherfucker fucker motherfucker => 101
    fucker motherfucker fucker => 010
    fucking
      motherfucker fucker motherfucker => 101101
    motherfucking
      motherfucker fucker motherfucker => 101101101101
    motherfucking
      fucker motherfucker => 01010101
    motherfucking fucking
      motherfucker fucker => 1010101010101010
    motherfucking motherfucking
      fucker motherfucker => 01010101010101010101010101010101



### 3.3 Supplementary Statements

The supplementary statement is the first non-multi-line statement that comes after a multi-line statement. A full statement usually consists of non-multi-line, multi-line and supplementary statements. A supplementary statement allows "fucker", "motherfucker", "fucking", "motherfucking", "fuckers" and "motherfuckers" to be used as the first keywords. However, "fuck" and "fucked" are forbidden. If a supplementary statement is not necessary, it should just be empty (contain only a single newline character, spaces or tabs).

    fuckers fucked fucking    (Non-multi-line)
      fucker motherfucker     (Multi-line)
    motherfucker              (Supplementary)
    fuck fuckers              (Non-multi-line)


### 3.4 Stacking

It's possible to have multi-line statements inside multi-line statements. Keywords in multi-line statements are only affected by the first upper sequence of *"fucking"* or *"motherfucking"* keywords. Subsequently, the result of that statement is affected by the next upper sequence of *"fucking"* or *"motherfucking"* keywords. All multi-line statements, stacked or non-stacked, must not be empty. When all multi-line statements are finished, the next line is a supplementary statement.



## 4. Storage

To store a number in one of the storages, use:

    fuckers fucked fucking
      fucker motherfucker (stores 0101 in "fuckers")

or

    motherfuckers fucked motherfucking
      fucker motherfucker (stores 01010101 in "motherfuckers")

Then it's a matter of outputting the value in the storages:

    fuck fuckers

or

    fuck motherfuckers



## 5. Output

Depending on the implementation, the Fuck language's output can either be directed to stdout (usually directed to a console) or serve as the returning value of a function in another language.

*"fuck"* outputs the **UTF-8** representation of a binary number:

    fuckers fucked motherfucker motherfucking
      fucker
    fucker motherfucker (Stores 01000001 in "fuckers")
    fuck fuckers (Outputs the letter "A")
    motherfuckers fucked fucking
      motherfucker
    motherfucker fucking
      fucker
    fucking
      motherfucker fucker motherfucker
    fucking
      fucker
    fucking
      motherfucker fucker fucker
    fucking
      motherfucker
    motherfucker fucking
      fucker (Stores 111001011010010010011100 in "motherfuckers")
      
    fuck motherfuckers (Outputs 夜)
    
**NOTE**: The way the binary number is constructed (from left to right or right to left) is irrelevant since UTF-8 does not care about byte order.  
**NOTE**: If the constructed binary number is too large (for example, it occupies more than 32 bits when the storages can only store up to 32 bits), the result will overflow and *fuck* will print a completely different UTF-8 representation than the one expected.



## 6. Validation Procedures

### 6.1 Non-multi-line Statements


#### 6.1.1 First Keyword

6.1.1.1 *"fuck"* MUST be a first keyword if used.  
6.1.1.2 *"fuckers"* or *"motherfuckers"* are ONLY allowed as first keywords BEFORE a *"fucked"* keyword.  
6.1.1.3 *"fucker"*, *"motherfucker"*, *"fucking"* and *"motherfucking"* must NOT be the first keywords in non-multi-line statements.


#### 6.1.2 Second Keyword

6.1.2.1 The ONLY obligatory second keyword is *"fucked"*, AFTER a *"fuckers"* or *"motherfuckers"*.  
6.1.2.2 *"fucked"* must afterwards accept at least one valid keyword.


#### 6.1.3 Last Keywords

6.1.3.1 *"fucking"* or *"motherfucking"* MUST be the last keywords of a **LINE** if used.  
6.1.3.2 When *"fucking"* or *"motherfucking"* are first encountered, the only acceptable keywords afterwards in the same **LINE** are *"fucking"* and *"motherfucking"*.


#### 6.1.4 Single Keywords in a Line

6.1.4.1 Lines in non-multi-line statements must contain at least 2 valid keywords. Lines in multi-line and supplementary statements are able to contain only 1 valid keyword.


### 6.2 Multi-line Statements

6.2.1 *"fucker"*, *"motherfucker"*, *"fuckers"*, *"motherfuckers"*, *"fucking"* and *"motherfucking"* are allowed as first keywords, although rules 6.1.3.1 and 6.1.3.2 still apply.  
6.2.2 *"fuck"* and *"fucked"* are forbidden.  
6.2.3 Lines in multi-line-statements must not be empty (contain only a single newline character, spaces or tabs).


### 6.3 Supplementary Statements

6.3.1 Rule 6.2.1 applies.  
6.3.2 Rule 6.2.2 applies.


### 6.4 Other Important Rules

6.4.1 *"fuck"* and *"fucked"* must NEVER appear in the same line.



## Annex A (informative) The C Fuck Interpreter

### A.1 Input Parameters

The possible input parameters are:

  - *No parameters / Invalid parameters* (Run in Interactive Mode with 4 multi-line indentation spaces)
  - *-h* (Display help)
  - *-f "FILE_NAME"* (Run in Read File Mode)
  - *-s "NUM"* (Run in Interactive Mode with NUM multi-line indentation spaces. NUM must be between 1 and 8)

All input parameters are mutually exclusive to one another.


#### A.1.1 Interactive Mode

Interactive Mode takes a single line of text from stdin until it encounters a newline character. It will then validate the line before processing it. This process then repeats. Pressing Ctrl+D will exit the program. There are 2 types of prompt characters in Interactive Mode:

  - *>* (Indicates a non-multi-line statement by itself. It will multiply based on the set number of indentation spaces and multi-line statements stacked on one another)
  - *S>* (Indicates a supplementary statement)


#### A.1.2 Read File Mode

Read File Mode takes a file that contains Fuck code. It will accordingly validate and process each line until EOF or when an error happens.


#### A.1.3 Multi-line Indentation Spaces

Providing the *"-s NUM"* parameter will make the program run in Interactive Mode and indent the line by NUM spaces every time "fucking" or "motherfucking" are encountered. By default, 4 multi-line indentation spaces are provided.


### A.2 Error Handling

In case an invalid statement is found, descriptive errors are sent to stderr:

  - Input parameter errors include the *source code file*, *function* and *line* that threw the error.
  - Interactive Mode and Read File Mode include the *source code file*, *function* and *line*, plus the *statement line* and the *position of the keyword* that caused the error.



## Annex B (informative) Fuck Vim Syntax Files

The Vim syntax files for Fuck are located in the *extra* folder:

  - The contents of *.vimrc* must be **appended** to your *.vimrc* file
  - The contents of *.vim* must be copied to the *.vim* folder in your home directory