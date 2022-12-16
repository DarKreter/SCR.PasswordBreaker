MD5 password breaking program with dictionary attack. 

Program works on configurable size of threads and try different combination of passwords from dictionary file.
It tries words on lower-case, upper-case and first letter with upper-case.
Configuring `charset` variable will change from what characters pre and post-fixes are created.
Double word combination are also supported.

```mkdir build
cd build
cmake ..
cmake --build . --target firmware

./firwmware/firmware $DICT_FILE$ $PASSWORD_FILE$
```
