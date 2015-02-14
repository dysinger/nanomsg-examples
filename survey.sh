./bin/survey server ipc:///tmp/survey.ipc & server=$!
./bin/survey client ipc:///tmp/survey.ipc client0 & client0=$!
./bin/survey client ipc:///tmp/survey.ipc client1 & client1=$!
./bin/survey client ipc:///tmp/survey.ipc client2 & client2=$!
sleep 3
kill $server $client0 $client1 $client2

