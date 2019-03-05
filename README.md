# fsize - show file size ranking int directory with colors and details.
- Show the list of large files in the specified directory with details, such as modified time, accessed time, file description.
- Files are sorted by file size in descending order.

## Features 
- File paths are colored in accordance with LS_COLORS
- File type is described by using libmagic

## Usage
```
$ ./fsize [-r] [-n num] [directory]
```

## Dependency
- This command needs libmagic to get file description. For example,  


## Example
- Without specifying directory, fsize analyze current directory.
- Path names are colored depending on the file types.
![current](./screenshots/screenshot_current.png)

- You can specify directory which is to be analyzed.
![current](./screenshots/screenshot_dir.png)

