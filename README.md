# CBT Requirements Calculator

Given a Conditional Behavior Tree (CBT) this program is able to compute the requirements necessary to successfully complete at least one of the plans encoded by the CBT itself.

## Installation

### Requirements 

##### Compile

You will need the gcc compiler (with c++11 support) installed on your computer. 
In order to check if you have gcc installed on your machine you can issue the command:

`gcc --version`

If the message  *command not found* appears that it means that gcc is not installed on your machine.  

##### External Program 

In order to check the satisfiability of the propositional logic encoding, we deploy the external program `limboole`which can be downloaded and deployed by following the steps below:

1. Limboole deploys *PicoSAT* as backend. If you do not have it on yuor machine, follow the steps below:
     * dowload the file picosat-965..tar.gz that you can find at the link http://fmv.jku.at/picosat/
     * decompress the downloaded file
     * rename the folder picosat-965 to picosat
     * in the picosat folder execute `./configure.sh && make`.

2. Once you have *PicoSAT* go to the link http://fmv.jku.at/limboole/
3. Dowload the file **limboole1.1.tar.gz**
4. Decompress the dowloaded file in the **same folder** in which the picosat folder is placed 
5. In the decompressed folder (limboole1.1) execute the command `./configure.sh && make`.

### Clone

Clone on your machine the repository `CBT_Requirements_Calculator`

### Compile 

In the folder CBT_Requirements_Calculator execute the command `make compile`.  
The object fles will be built in the build folder. 

## How to use it

In order to deploy this program, open the Makefile in the folder CBT_Requirements_Calculator and set the following parameters:

The parameter INFILE must be set equal to the string containg the path of the input file:

`INFILE = "/path_to_the_input_file.xml"`

The parameter OUTFOLDER must be set equal to the string containg the path of the folder in which you would like to save your output files. 

`OUTFOLDER = "/path_to_the_output_folder"`

The LIMBOOLEPATH  must be set equal to the string containg the path of the **executable limboole program**. 

`LIMBOOLEPATH ="/path_to_the_limboole_executable"`

Once the above parameters are set, execute `make run` and the output files will be generated in the folder specified by `OUTFOLDER`.

The program can also be directly launched (from the bin folder if the command `make compile` has already been issued) with the following inputs (follow the order given below):
- a string containing the path of the .xml input file,
- a string containing the path of the folder in which the output files will be created, and
- a string containing the path of the limboole executable program.

### Output Files

The program generates three files in the folder `./output`:
- `BTplans.txt`: in this file the propositional logic representation of the CBT is written,
- `general_requirements.txt`: the first line of this file declares if the representation contained in `BTplans.txt` is satisfiable; if that is the case it also shows a model of such representation, 
- `initial_requirements.txt`: this file contains only the assignments of the variables corresponding to the initial time step (t=0).

## Options

If you want to delete the executable file and all the object files `.o` in the build folder issue the command `make clean`.

## Testing

For the testing phase the framework catch2 (https://github.com/catchorg/Catch2) was deployed.
The tool can be tested by executing the command:

`make test`

in this way all the tests will be executed.

