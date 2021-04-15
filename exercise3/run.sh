set -xe
echo "=====test.in===="
cat test.in
gcc open.c -o open
echo "=====open.c output===="
./open
sleep 0.1
echo "=====test.out====="
cat test.out