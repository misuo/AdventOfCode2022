_Took way too long for this. Rather than coding my own tree and visitors, I ended up simply to collect directories and their sizes into a collection, "std::map<dir,size>" used. This was my initial gut feeling, but was of course afraid of what part II might bring. It paned out. I do however also have a version using Boost Graph Library (BGL), building up the "file system" of directories and files._

### A few things that may affect solution

* What if `ls` already has been done once for current directory? `ls` can in principle be done on the same directory multiple times
* Between `ls`s new files could have been added or deleted! A file (same name) and its size could even have changed!
* a `dir` may be shown in `ls` that we do not necessary do a `ls` for - hence unknown content.
* Can you have a directory and file with same name? Yes!
* Can you have multiple directories with same name? Yes, just at different paths.
