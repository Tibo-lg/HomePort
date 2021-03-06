# Copyright 2013 Aalborg University. All rights reserved.
#  
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions
# are met:
# 
# 1. Redistributions of source code must retain the above copyright
# notice, this list of conditions and the following disclaimer.
# 
# 2. Redistributions in binary form must reproduce the above copyright
# notice, this list of conditions and the following disclaimer in the
# documentation and/or other materials provided with the distribution.
# 
# THIS SOFTWARE IS PROVIDED BY Aalborg University ''AS IS'' AND ANY
# EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
# IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
# PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL Aalborg University OR
# CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
# SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
# LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF
# USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
# ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
# OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
# OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
# SUCH DAMAGE.
# 
# The views and conclusions contained in the software and
# documentation are those of the authors and should not be interpreted
# as representing official policies, either expressed.

# Configure files to run examples
configure_file(CA_root_cert.pem CA_root_cert.pem COPYONLY)
configure_file(HPD-cert.pem HPD-cert.pem COPYONLY)
configure_file(HPD-key.key HPD-key.key COPYONLY)
configure_file(client-browser-cert.p12 client-browser-cert.p12 COPYONLY)
configure_file(client-cert.pem client-cert.pem COPYONLY)
configure_file(hpd.cfg hpd.cfg COPYONLY)

# Example
add_executable(hpd_example EXCLUDE_FROM_ALL
      hpd_example.c
      )
target_link_libraries(hpd_example hpd ev)
add_dependencies(example hpd_example)

add_executable(hpd_example_timer EXCLUDE_FROM_ALL
      hpd_example_timer.c
      )
target_link_libraries(hpd_example_timer hpd ev)
add_dependencies(example hpd_example_timer)

add_executable(hpd_example_easy EXCLUDE_FROM_ALL
      hpd_example_easy.c
      )
target_link_libraries(hpd_example_easy hpd ev)
add_dependencies(example hpd_example_easy)

add_executable(hpd_phidget EXCLUDE_FROM_ALL
      hpd_phidget.c
      hpd_phidget_example.c
      )
target_link_libraries(hpd_phidget hpd ev phidget21)
add_dependencies(example hpd_phidget)

