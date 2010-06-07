/*
* Copyright (c) 2008, AMT – The Association For Manufacturing Technology (“AMT”)
* All rights reserved.
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions are met:
*     * Redistributions of source code must retain the above copyright
*       notice, this list of conditions and the following disclaimer.
*     * Redistributions in binary form must reproduce the above copyright
*       notice, this list of conditions and the following disclaimer in the
*       documentation and/or other materials provided with the distribution.
*     * Neither the name of the AMT nor the
*       names of its contributors may be used to endorse or promote products
*       derived from this software without specific prior written permission.
*
* DISCLAIMER OF WARRANTY. ALL MTCONNECT MATERIALS AND SPECIFICATIONS PROVIDED
* BY AMT, MTCONNECT OR ANY PARTICIPANT TO YOU OR ANY PARTY ARE PROVIDED "AS IS"
* AND WITHOUT ANY WARRANTY OF ANY KIND. AMT, MTCONNECT, AND EACH OF THEIR
* RESPECTIVE MEMBERS, OFFICERS, DIRECTORS, AFFILIATES, SPONSORS, AND AGENTS
* (COLLECTIVELY, THE "AMT PARTIES") AND PARTICIPANTS MAKE NO REPRESENTATION OR
* WARRANTY OF ANY KIND WHATSOEVER RELATING TO THESE MATERIALS, INCLUDING, WITHOUT
* LIMITATION, ANY EXPRESS OR IMPLIED WARRANTY OF NONINFRINGEMENT,
* MERCHANTABILITY, OR FITNESS FOR A PARTICULAR PURPOSE. 

* LIMITATION OF LIABILITY. IN NO EVENT SHALL AMT, MTCONNECT, ANY OTHER AMT
* PARTY, OR ANY PARTICIPANT BE LIABLE FOR THE COST OF PROCURING SUBSTITUTE GOODS
* OR SERVICES, LOST PROFITS, LOSS OF USE, LOSS OF DATA OR ANY INCIDENTAL,
* CONSEQUENTIAL, INDIRECT, SPECIAL OR PUNITIVE DAMAGES OR OTHER DIRECT DAMAGES,
* WHETHER UNDER CONTRACT, TORT, WARRANTY OR OTHERWISE, ARISING IN ANY WAY OUT OF
* THIS AGREEMENT, USE OR INABILITY TO USE MTCONNECT MATERIALS, WHETHER OR NOT
* SUCH PARTY HAD ADVANCE NOTICE OF THE POSSIBILITY OF SUCH DAMAGES.
*/

#include "internal.hpp"
#include "haas_adapter.hpp"
#include "server.hpp"
#include "string_buffer.hpp"

int main(int aArgc, char *aArgv[])
{
  int port = 7878;
  int i = 1;
  bool debug = false;
  bool positions = false;

  while (aArgv[i][0] == '-' && aArgc > 0)
  {
    if (aArgv[i][1] == 'd')
      debug = true;
    else if (aArgv[i][1] == 'p')
      positions = true;
    else
    {
      printf("Invalid option: %s\n", aArgv[i]);
      printf("Usage: %s [-dp] <Serial_COM> [port]\n", aArgv[0]);
      exit(1);
    }

    i++;
    aArgc--;
  }

  if (aArgc < 2)
  {
    printf("Usage: %s <Serial_COM>\n", aArgv[0]);
    exit(1);
  }

  if (aArgc > 2)
    port = atoi(aArgv[i + 1]);
    
  /* Construct the adapter and start the server */
  HaasSerial *serial = new HaasSerial(aArgv[i], 19200, "none", 7, 1, debug);
  HaasAdapter adapter(port, serial, positions);
  adapter.startServer();
  
  return 0;
}
