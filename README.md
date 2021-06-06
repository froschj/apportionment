# apportionment

Program to apportion a number of congressional seats among states according to population.

For more information about the methods, see the support materials.

`make apportioner` requires g++

# usage note from command line

USAGE: 

   apportioner  [-h] [--version] [-f <filename>] [-m <adams|dean|
                huntingtonhill|jefferson|webster>] [-o <filename>] [-p
                <filename>] [seats]


Where: 

   -m <adams|dean|huntingtonhill|jefferson|webster>,  --method <adams|dean|
      huntingtonhill|jefferson|webster>
     Apportionment Method

   -f <filename>,  --file <filename>
     Input File Name (CSV <state>,<population>)

   -o <filename>,  --output <filename>
     Output File Name (CSV <state>,<seats>)

   -p <filename>,  --priority <filename>
     Priority List File Name (CSV <seat number>,<priority value>,<state>,
     <state seats>)

   --,  --ignore_rest
     Ignores the rest of the labeled arguments following this flag.

   --version
     Displays version information and exits.

   -h,  --help
     Displays usage information and exits.

   seats <Positive Number > number of states>
     Number of seats to apportion

   Apportionment Calculator