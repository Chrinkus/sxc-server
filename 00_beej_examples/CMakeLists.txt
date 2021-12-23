cmake_minimum_required(VERSION 3.18)

project(beej-tutorials VERSION 0.1 LANGUAGES C)

# first example
add_executable(showip showip.c)

# client-server tcp example
add_executable(server server.c)
add_executable(client client.c)

# "client"-"server" udp example
add_executable(listener listener.c)
add_executable(talker talker.c)

# poll() example
add_executable(poller poll.c)

