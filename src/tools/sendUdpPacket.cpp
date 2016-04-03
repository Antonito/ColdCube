#include "common_structs.hpp"
#ifdef _WIN32
#else
# include <stdio.h>
# include <unistd.h>
#endif

int		sendUdpPacket(t_data *data, char packet[42])
{
  unsigned int	len;

  len = sizeof(data->net.udp.to_serv);
  if (sendto(data->net.udp.sock, packet, 42, 0,
                 (struct sockaddr *)&data->net.udp.to_serv, len) == -1)
    return (1);
  return (0);
}
