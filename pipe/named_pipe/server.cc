#include "comm.hpp"

int main()
{
    bool r = createFifo(NAMED_PIPE);
    assert(r);
    (void)r;

    std::cout << "server begin" << std::endl;
    int rfd = open(NAMED_PIPE, O_RDONLY);
    std::cout << "server end" << std::endl;

    if (rfd < 0)
        exit(1);

    // read
    char buffer[1024];
    while (true)
    {
        ssize_t s = read(rfd, buffer, sizeof(buffer) - 1);
        if (s > 0)
        {
            buffer[s] = 0;
            std::cout << "client->srver# " << buffer << std::endl;
        }
        else if(s == 0)
        {
            std::cout << "client quit,me too!" << std::endl;
            break;
        }
        else
        {
            std::cout << "err string: " << strerror(errno) << std::endl;
            break;
        }
    }

    close(rfd);
    // sleep(10);
    removeFifo(NAMED_PIPE);
    return 0;
}
