/***********************************************************************/
/*                                                                     */
/*                           Objective Caml                            */
/*                                                                     */
/*  Xavier Leroy and Pascal Cuoq, projet Cristal, INRIA Rocquencourt   */
/*                                                                     */
/*  Copyright 1996 Institut National de Recherche en Informatique et   */
/*  en Automatique.  All rights reserved.  This file is distributed    */
/*  under the terms of the GNU Library General Public License.         */
/*                                                                     */
/***********************************************************************/

/* $Id$ */

#include <mlvalues.h>
#include "unixsupport.h"
#include <winsock.h>
#include <sys/types.h>

static int sockopt[] = {
  SO_DEBUG, SO_BROADCAST, SO_REUSEADDR, SO_KEEPALIVE, 
  SO_DONTROUTE, SO_OOBINLINE };

value unix_getsockopt(socket, option) /* ML */
     value socket, option;
{
  int optval, optsize;
  optsize = sizeof(optval);
  if (getsockopt((SOCKET) Handle_val(socket), SOL_SOCKET, 
                 sockopt[Int_val(option)], (char *) &optval, &optsize) == -1)
    unix_error(WSAGetLastError(), "getsockopt", Nothing);
  return Val_int(optval);
}

value unix_setsockopt(socket, option, status) /* ML */
     value socket, option, status;
{
  int optval = Int_val(status);
  if (setsockopt((SOCKET) Handle_val(socket), SOL_SOCKET,
                 sockopt[Int_val(option)],
                 (char *) &optval, sizeof(optval)) == -1)
    unix_error(WSAGetLastError(), "setsockopt", Nothing);
  return Val_unit;
}
