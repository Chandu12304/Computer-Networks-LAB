set ns [new Simulator]

set tf [open lab1.tr w]
$ns trace-all $tf

set nf [open lab1.nam w]
$ns namtrace-all $nf

set n0 [$ns node]
set n1 [$ns node]
set n2 [$ns node]

$ns duplex-link $n0 $n2 10Mb 300ms DropTail
$ns duplex-link $n1 $n2 1Mb 300ms DropTail #bottle neck

$ns queue-limit $n0 $n2 10
$ns queue-limit $n2 $n1 5 #bottle neck and direction imp

set u0 [new Agent/UDP]
$ns attach-agent $n0 $u0

set cbr0 [new Application/Traffic/CBR]
$cbr0 attach-agent $u0

set sink0 [new Agent/Null]
$ns attach-agent $n1 $sink0

$ns connect $u0 $sink0

$cbr0 set packetSize_ 500
$cbr0 set interval_ 0.001 # bottle

$ns color 1 "red"

$n0 label "Source/UDP/CBR"
$n1 label "Destination"
$n2 label "Router/Sink_Null"

$u0 set class_ 1

proc finish {} {
global ns nf tf
$ns flush-trace
exec nam lab1.nam &
close $tf
close $nf
exit 0
}

$ns at 0.1 "$cbr0 start"
$ns at 4 "finish"

$ns run
