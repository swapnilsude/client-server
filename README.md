# Client Server using Internet domain sockets
An arithmetic calculator service is available at a server. Client processes send their arithmetic operation requests to the server and get the result back. The arithmetic expression can be of the form “a <operator> b”, where a and b are integers and a,b ≥ 0 and operator is one of {+, -, * , /}.  Any other arithmetic expression (or any other form of input) will return error. Client does not parse the arithmetic expression it is done at the server. To  keep  it  simple,  the  division  operation  should be integer division. When the user enters “exit” the client program will end. The server is capable to handle multiple clients running at the same time.
  
#### To create both server and client binaries:
make all
#### To create server binary:
make server
#### To create client binary:
make client
#### To clean both server and client binaries:
make clean
#### To clean server binary:
make clean_server
#### To clean client binary:
make clean_client
