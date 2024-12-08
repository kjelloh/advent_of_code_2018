# advent_of_code_2018
My solutions to 2018 Advent of code

To use the Z-shell scripts. 
* **init_day.zsh**: Call init_day.zsh with the day number and it will copy template code from the day_0 sub-folder.
* **tool_chain.txt**: Echo the CMake generator name (e.g., 'Xcode') to tool_chain.txt to make day_n/init_tool_chain.zsh to generate the tool chain of choise.
* **init_tool_chain.zsh**: cd into day sub-folder and execute init_tool_chain.zsh to have CMake generate your tool chain.
* **cookie.txt**: Echo your Advent of Code Session Key cookie value into the top-folder file file cookie.txt. This value is used by sub-folder day_n script pull_data.zsh to fetch the inoput data for the day.
* **pull_data.zsh**: Call pull_data.zsh to download the input data for the set year and day.
* **year.txt** and **day.txt**: Contains year and day set and used by the zsh_scripts above.

## Traps i fell into solving AoC 2018

None so far ;)