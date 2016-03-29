#include "common_structs.hpp"

int		sendUdpPacket(t_data *data, char packet[70])
{
  unsigned int	len;

  len = sizeof(data->net.udp.to_serv);
  if (sendto(data->net.udp.sock, packet, 70, 0,
                 (struct sockaddr *)&data->net.udp.to_serv, len) == -1)
    return (1);
  return (0);
}