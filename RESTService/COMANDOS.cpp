apt-get update -y
apt-get install -y libcpprest-dev
g++ -std=c++11 RestService.cpp -o test.o -lboost_system -lcrypto -lssl -lcpprest