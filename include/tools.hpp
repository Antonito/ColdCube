#ifndef	TOOLS_H_
# define TOOLS_H_

# include <GL/gl.h>
# include "common_structs.hpp"

void	drawText(char *, int, int, GLfloat, GLfloat, GLfloat);
int	sendUdpPacket(t_data *, char []);
int	clientLaunchTcpc(t_data *);
int	clientLaunchUdpc(t_data *);
int	createUdpPacket(t_data *, t_player *);
int	readUdpPacket(t_data *);
bool	checkPacket(char *);

#endif	/* !TOOLS_H_ */
