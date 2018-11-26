# MIPT_CW_MPI

Решение [контрольной работы](https://github.com/fufler/mipt-cs-samples/blob/master/exam.md) по MPI для студентов МФТИ.

## Как запускать
### Предустановка программ
#### OS Fedora
```bash
sudo yum install openmpi-devel openmpi mpich2 g++
```
#### OS Ubuntu
```bash
sudo apt-get install openmpi-devel openmpi mpich2 g++
```
#### OS Debian / Mint
```bash
sudo apt install openmpi-devel openmpi mpich2 g++
```
### Компиляция
```bash
mpic++ integral.cpp -o integral
```
### Запуск
```bash
mpirun -np <КОЛИЧЕСТВО ПРОЦЕССОВ> ./integral <ГЛУБИНА ИНТЕГРИРОВАНИЯ>
```
