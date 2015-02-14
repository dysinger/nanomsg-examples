./bin/pubsub server ipc:///tmp/pubsub.ipc & server=$! && sleep 1
./bin/pubsub client ipc:///tmp/pubsub.ipc client0 & client0=$!
./bin/pubsub client ipc:///tmp/pubsub.ipc client1 & client1=$!
./bin/pubsub client ipc:///tmp/pubsub.ipc client2 & client2=$!
sleep 5
kill $server $client0 $client1 $client2
