mkfifo pipe1
mkfifo pipe2

exec 33<>pipe1
exec 53<>pipe2
./riddle 34>&33 54>&53
rm pipe1 pipe2

