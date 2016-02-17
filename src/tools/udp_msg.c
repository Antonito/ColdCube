void		send_udp(int sock, char *msg, struct sockaddr dest)
{
  int		len;

  len = sizeof(dest);
  sendto(sock, msg, 120, 0, dest, len); /* change here the size of str packet */
}

void		recv_udp(int sock, char *msg, struct sockaddr src)
{
  int		len;

  len = sizeof(src);
  recvfrom(sock, msg, 120, 0, src, len); /* change here the size of str packet */
}
