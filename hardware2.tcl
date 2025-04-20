set ns [new Simulator]

set tf [open lab2.tr w]
$ns trace-all $tf

set nf [open lab2.nam w]
$ns namtrace-all $nf

set n0 [$ns node]
set n1 [$ns node]
set n2 [$ns node]
set n3 [$ns node]

$ns duplex-link $n0 $n2 10Mb 10ms DropTail
$ns duplex-link $n1 $n2 10Mb 10ms DropTail
$ns duplex-link $n2 $n3 1Mb 10ms DropTail 

$ns queue-limit $n0 $n2 10
$ns queue-limit $n1 $n2 10
$ns queue-limit $n2 $n3 5

set udp0 [new Agent/UDP]
$ns attach-agent $n0 $udp0

set tcp0 [new Agent/TCP]
$ns attach-agent $n1 $tcp0

set cbr0 [new Application/Traffic/CBR]
$cbr0 attach-agent $udp0

set ftp0 [new Application/FTP]
$ftp0 attach-agent $tcp0

set udp0Sink [new Agent/Null]
$ns attach-agent $n3 $udp0Sink

set tcp0Sink [new Agent/TCPSink]
$ns attach-agent $n3 $tcp0Sink

$ns connect $udp0 $udp0Sink
$ns connect $tcp0 $tcp0Sink

$cbr0 set packetSize_ 500
$cbr0 set interval_ 0.01
$ftp0 set packetSize_ 500
$ftp0 set interval_ 0.01

$ns color 1 "red"
$ns color 2 "blue"

$udp0 set class_ 1
$tcp0 set class_ 2

$n0 label "Source1/UDP"
$n1 label "Source/TCP"
$n2 label "Router"
$n3 label "Destination/Sink"


proc finish {} {
global ns nf tf
$ns flush-trace
exec nam lab2.nam &
close $nf
close $tf
exit 0
}

$ns at 0.1 "$cbr0 start"
$ns at 0.1 "$ftp0 start"
$ns at 4 "finish"

$ns run
