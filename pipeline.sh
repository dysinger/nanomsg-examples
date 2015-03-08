./bin/pipeline node0 ipc:///tmp/pipeline.ipc & node0=$! && sleep 1
./bin/pipeline node1 ipc:///tmp/pipeline.ipc "Hello, World!"
./bin/pipeline node1 ipc:///tmp/pipeline.ipc "Goodbye."
kill $node0

