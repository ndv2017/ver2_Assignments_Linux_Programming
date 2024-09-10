#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#define LISTEN_BACKLOG      20
#define MAXBUF              100
#define handle_error(msg) \
    do { perror(msg); exit(EXIT_FAILURE); } while (0)

void chat_func(int new_socket_fd)
{
    char recv_buffer[MAXBUF];
    char send_buffer[MAXBUF];

    while (1)
    {
        if (read(new_socket_fd, recv_buffer, sizeof(recv_buffer)) == -1)
            handle_error("read failed");

        if (strncmp("exit", recv_buffer, 4) == 0) 
        {
            system("clear");
            break;
        }

        printf("\nMessage from client: %s\n", recv_buffer);

        printf("Respond message: ");
        fgets(send_buffer, MAXBUF, stdin);

        if (write(new_socket_fd, send_buffer, sizeof(send_buffer)) == -1)
            handle_error("write failed");

        if (strncmp("exit", send_buffer, 4) == 0) 
        {
            system("clear");
            break;
        }
    }
    
    close(new_socket_fd);
}

int main(int argc, char const *argv[])
{
    int port_no, len;
    int server_fd, new_socket_fd;
    struct sockaddr_in server_addr, client_addr;

    if (argc < 2)
    {
        printf("Not enough arguments.\nCommand: ./server <port number>\n");
        exit(EXIT_FAILURE);
    }
    else
        port_no = atoi(argv[1]);
    

    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == -1)
        handle_error("socket failed");
    
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(port_no);

    if (bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1)
        handle_error("bind failed");

    if (listen(server_fd, LISTEN_BACKLOG) == -1)
        handle_error("listen failed");

    len = sizeof(client_addr);

    while (1)
    {
        printf("Server is listening at port: %d\n", port_no);
        puts("....");
        new_socket_fd = accept(server_fd, (struct sockaddr *)&server_addr, (socklen_t *)&len);
        if (new_socket_fd == -1)
            handle_error("accept failed");
        
        system("clear");

        printf("Server: Got connection!\n");
        chat_func(new_socket_fd);
    }

    close(server_fd);
    
    return 0;
}