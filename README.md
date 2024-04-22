<H1> Genuis Song Title Parser </h1>
<i>COP3530 Project 3 - Tiffany Vo, Ethan King, Evan Stice</i>
<br>Video link

<h2> Usage </h2>

This program takes in a dataset of over 150,000 songs from the Genius Lyric Database. Song titles are stored in our implementations of both ordered and unordered maps, and for each function the performance (time to execute in ms) is displayed for each data structure. Each function involves parsing data from song titles.

When the program is run, the dataset is loaded into both map data structures, and the execution times for both of these tasks are displayed in the output. Then, a list of options is displayed:

### <i>Option 1:</i> Most used words in song titles

This function returns the top 5 most used words in song titles in the dataset. A cooresponding percentage is displayed next to each of the top five words, showing the percentage of songs within the entire dataset that contain the word. Execution times for both data structures are displayed after these operations are complete.

### <i>Option 2:</i> Percentage of songs that contain a specific word

This function takes in a specific word or phrase from the user and returns the percentage of songs in the dataset that contain this word. Execution times for both data structures are displayed after these operations are complete. 

### <i>Option 3:</i> Search for a song

This function allows the user to input a song title to see if it is included in the dataset. This is primarily used to showcase the search performance of our implementations. Execution times for both data structures are displayed after these operations are complete.

### <i>Option 4:</i> Quit

The exit message displays, and the program quits.

<i>After each operation, the user is asked if they would like to continue using the program or quit. If they select "Y", the program loops back to the option menu. If "N" is selected, the program displays the exit message and quits.</i>

<h2> More information </h2>

For more information regarding the proposal of our project, implementation details, resources used, and more, please refer to the attached "Report.pdf" included in this repository.
