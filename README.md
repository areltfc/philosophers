## _Philosophers_
##### _A problem with threads_

A school project in which threads have to share memory space and mutexes.

#### How to compile?
Just run this in the philosophers folder
```sh
$ make
```

To clean it up, run
```sh
$ make fclean
```

#### How to run philosophers?

You first need to export the library used by the program:
```sh
$ export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:`pwd`/lib
```

Project realised in February/March 2018 by Charles CASTELAIN and (yours truly) Arthur DELATTRE