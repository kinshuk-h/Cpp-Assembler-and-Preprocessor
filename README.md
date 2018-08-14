# C++ Assembler and Preprocessor
A WinAPI program to generate assembly and/or preprocessor files on the go.

## Description 
The following code generates assembly and/or preprocessor dump files from a C++ source code file, when the user clicks on the respective buttons. The code is developed using C++, with an extensive use of WinAPI Functions for providing a primitive graphical interface.

## How to use
#### 1. General Use
   - Launch the utility, ensuring that all the necessary files are in the same folder.
   - Right - Click on any icon to know more about the function is offers.
   - Select one of the options, and follow the steps mentioned below.
#### 2. Assembly File Generation
   - Upon selecting this utility, the user is prompted to select a C++ file to generate assembly file of.
   - After selection, the compilation occurs in the background, and the user is notified upon completion.
#### 3. Preprocessor File Generation
   - This function is similar in operation to 'Assembly File generation', but in this case, the preprocessor file is generated.
   - The extra files, if present before processing, are ignored. Any errors, if they exist, are not shown though.
#### 4. Settings Panel
   - The panel offers the user the ability to select a compiler between `GNU GCC (v.4.8+)` & `LLVM Clang (v3.5+)`.
   - The user must also specify the path to the compiler, by browsing for it in the computer. If an incorrect path is 
     mentioned, an error message is thrown.
   - The user can also specify additional flags to be passed to the compiler during file generation. The flags that are allowed 
     are `-std=c++<ver>`, `-l<lib_name>`, `-masm=<syntax>`, `-S` & `-save-temps`. 
     - Eg : ``` -std=c++17 -S -save-temps -lkernel32 -luser32 -lcomdlg -masm=intel ```

## Screenshots

![Main Page](https://raw.githubusercontent.com/kinshuk-h/Cpp-Assembler-and-Preprocessor/master/Main%20Page.jpg)

![Settings Panel](https://raw.githubusercontent.com/kinshuk-h/Cpp-Assembler-and-Preprocessor/master/Settings.jpg)
