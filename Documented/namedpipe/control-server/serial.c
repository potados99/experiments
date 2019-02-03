#include "serial.h"

int serial_open(const char *port, int baudrate) {
  int fd = 0;
  time_t t = time(NULL);
  while ((fd = open(port, O_RDWR | O_NOCTTY | O_SYNC)) < 0) {
    if (time(NULL) - t >= SERIAL_TIMEOUT) ERROR("Error opening port. Timeout.\n")
  }

  _set_interface_attribs (fd, baudrate, 0); /* set speed to 9,600 bps, 8n1 (no parity) */
  _set_blocking (fd, 0);

	return fd;
}

bool serial_send(int fd, char delim, char *wbuf, char *rbuf, int rbufSize) {
  LOGF("Will write [%s]\n", command)

  ipc_write(fd, delim, wbuf);
  tcdrain(fd);
  LOGF("Did write [%s]\n", command)

  ipc_read(fd, delim, rbuf, rbufSize);
  LOGF("Read [%s]\n", buf)

  return TRUE;
}

void _set_interface_attribs (int fd, int speed, int parity) {
  struct termios tty;
  memset (&tty, 0, sizeof tty);
  if (tcgetattr (fd, &tty) != 0) ERROR("Error from tcgetattr.\n")

  cfsetospeed (&tty, speed);
  cfsetispeed (&tty, speed);

  tty.c_cflag = (tty.c_cflag & ~CSIZE) | CS8;     // 8-bit chars
  // disable IGNBRK for mismatched speed tests; otherwise receive break
  // as \000 chars
  tty.c_iflag &= ~IGNBRK;         // disable break processing
  tty.c_lflag = 0;                // no signaling chars, no echo,
  // no canonical processing
  tty.c_oflag = 0;                // no remapping, no delays
  tty.c_cc[VMIN]  = 0;            // read doesn't block
  tty.c_cc[VTIME] = 5;            // 0.5 seconds read timeout

  tty.c_iflag &= ~(IXON | IXOFF | IXANY); // shut off xon/xoff ctrl

  tty.c_cflag |= (CLOCAL | CREAD);// ignore modem controls,
  // enable reading
  tty.c_cflag &= ~(PARENB | PARODD);      // shut off parity
  tty.c_cflag |= parity;
  tty.c_cflag &= ~CSTOPB;
  tty.c_cflag &= ~CRTSCTS;

  if (tcsetattr (fd, TCSANOW, &tty) != 0) ERROR("Error from tcsetattr.\n")
}

void _set_blocking (int fd, int should_block) {
  struct termios tty;
  memset (&tty, 0, sizeof tty);
  if (tcgetattr (fd, &tty) != 0) ERROR("Error from tggetattr.\n")

  tty.c_cc[VMIN]  = should_block ? 1 : 0;
  tty.c_cc[VTIME] = 5;            // 0.5 seconds read timeout

  if (tcsetattr (fd, TCSANOW, &tty) != 0) ERROR("Error setting term attributes.\n")
}
