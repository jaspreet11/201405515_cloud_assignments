#!usr/bin/python
from mininet.net import Mininet
from mininet.node import Controller
from mininet.cli import CLI
from mininet.log import setLogLevel, info
from mininet.link import TCLink
import sys

def mynet():
        print "Creating an empty network and the desired topology \n \n"


        print "enter desired no of hosts and switches \n \n"
        no_hosts = int(sys.argv[1])
        no_sw = int(sys.argv[2])

        net = Mininet( controller=Controller,link=TCLink)
        print "Controller added....\n \n"
        net.addController('c0')

        num_h = 1
        li = []
        print "Hosts and switches are being added \n \n"
        for p in range(no_sw):
                var = 's' + str(p+1)
                s = net.addSwitch(var)
                for q in range(no_hosts):
                        var2 = 'h' + str(num_h)
                        if num_h % 2 != 0:
                                h = net.addHost(var2, ip = "10.0.1.0/24", defaultRoute=None)
                        else:
                                h = net.addHost(var2, ip ="10.0.2.0/24", defaultRoute=None)
                        if num_h % 2 == 0:
                                net.addLink(h,s,bw = 2)
                        else:
                                net.addLink(h,s,bw = 1)


			 num_h = num_h + 1
                li.append(s)


        for p in range(no_sw):
                if q < no_sw - 1:
                        net.addLink(li[q],li[q+1],bw=2)

        print 'Starting network....\n \n'
        net.start()

        print 'Running CLI....\n\n '
        CLI( net )

        print 'Stopping network....\n \n'
        net.stop()

if __name__ == '__main__':
    setLogLevel( 'info' )
    mynet()

