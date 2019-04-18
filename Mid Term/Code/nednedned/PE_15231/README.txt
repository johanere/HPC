Compile using supplied make file, produces executable "main.exe", run as "./main.exe <filename> <d> <eps> <n>",
where <filename> is the name of the file to be read, <d> is the dampening factor, <eps> is the iteration threshold, and <n> the number of top pages to be displayed.
Run example of executable: "./main.exe web-NotreDame.txt 0.85 0.00001 4", using
<filename> = NotreDame.txt", <d>=0.85, <eps>=0.00001, <n>= 4.

openMP is set to use all available threads, OMP_NUM_THREADS=#desired_number_of_threads, should be used with program execution if this is undiserable 