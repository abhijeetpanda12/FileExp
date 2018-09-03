# FileExp
This repository is the final submission to my Operating Systems Assignment -1.
Submission Deadline : 3rd September, 2018

### The aim of the assignment is to make a terminal based File-Explorer application that can perform functionalities like browsing, listing, copying, moving, deleting, renaming, searching and snapshot.

## The application works with two major modes
## * Normal Mode
## * Command mode

### Start the application by:
```
make
./output /path/to/root/directory
```

## Normal Mode:
On Start of the application, the window remains in Normal Mode as default, displaying the contents of the root directory.
The display formay is like
```
num->|<File_Name>----------> <size>	<permissions>	<last_modified_time>
num->|[DIR]<Directory_Name>
```
A message bar at the bottom displays the instructions to quit or scroll(in case all the files don't fit in to the screen).
The `backspace` / `delete`(in Mac) can be pressed to move one level up the directory structure.
The `up` and the `down` arrow keys can be used to navigate through the files and directories displayed on the screen.
Pressing the `enter` key on a directory, enters into the directory and displays the content.
Pressing the `enter` key on a file, opens the file with the default application.
The `left` and `right` arrow keys can be used to move back and forward to the browsing history.
At any point in normal mode `q` can be pressed to quit the application.
`c` should be used for scrolling the window.
The `h` key can be pressed any time to reach the home directory.

## Command mode:
To enter the Command Mode from Normal Mode, the `:` key should be pressed.
The Command mode allows multiple file management functionalities like copying, moving, deleting, searching, rename,  snapshot.

To exit the Command mode, the `esc` key should be pressed. This will take the window to Normal Mode.

### goto a directory
```
:goto /path/to/directory
```
### creating a file
```
:create_file /path/to/file
```
### copying a file
```
:copy /path/to/source_file /path/to/destination_file
```
### copying a directory
The function recursively copies the directory.
```
:copy_dir /path/to/source_directory /path/to/destination_directory
```
### moving a file
```
:move /path/to/source_file /path/to/destination_file
```
### moving a directory
The function recursively moves the directory.
```
:move_dir /path/to/source_directory /path/to/destination_directory
```
### renaming a file/folder
```
:rename /path/to/file /path/to/new/file
```
### deleting a file
```
:delete /path/to/file
```
### deleting a directory
The function recursively deletes the directory.
```
:delete_dir /path/to/directory
```
### searching a file
The function recursively searches the current directory and displays the results.
```
:search file
```
### snapshot
The function recursively lists the contents of a directory in a file.
```
snapshot /path/to/directory /path/to/snapshot/file
```
## Limitations and Assumption:
### * The file and directory paths must be absolute.
### * Text Wrapping is not supported.
### * File and Folder Deletions are permanent.