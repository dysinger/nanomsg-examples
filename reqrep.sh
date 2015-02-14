./bin/reqrep node0 ipc:///tmp/reqrep.ipc & node0=$! && sleep 1
./bin/reqrep node1 ipc:///tmp/reqrep.ipc
kill $node0
