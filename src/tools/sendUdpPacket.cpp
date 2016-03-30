#include "common_structs.hpp"
#include <stdio.h>
#include <unistd.h>

int		sendUdpPacket(t_data *data, char packet[70])
{
  unsigned int	len;

  len = sizeof(data->net.udp.to_serv);

  printf("sock %d\n", data->net.udp.sock);
  printf("%p\n", packet);
  write(1, packet, 70);
  if (sendto(data->net.udp.sock, packet, 70, 0,
                 (struct sockaddr *)&data->net.udp.to_serv, len) == -1)
    return (1);
  return (0);
}
