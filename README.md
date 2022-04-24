# One_Time_Pad
 OTP encryption and decryption

<h2><strong>Program 4&nbsp;– CS 344</strong></h2>
<h2>Overview</h2>
<p>In this assignment, you will be creating five small programs that encrypt and decrypt information using a one-time pad-like system. I believe that you will find the topic quite fascinating: one of your challenges will be to pull yourself away from the stories of real-world espionage and tradecraft that have used the techniques you will be implementing.</p>
<p>These programs serve as a capstone to what you have been learning in this course, and will combine the multi-processing code you have been learning with socket-based inter-process communication. Your programs will also accessible from the command line using standard UNIX features like input/output redirection, and job control. Finally, you will write a short compilation script.</p>
<h2>Specifications</h2>
<p>All execution, compiling, and testing of this program should ONLY be done in&nbsp;the bash prompt on&nbsp;our&nbsp;class server!</p>
<p>Use the following link as your primary reference on One-Time Pads (OTP):</p>
<p><a href="http://en.wikipedia.org/wiki/One-time_pad" class="external" target="_blank" rel="noreferrer noopener"><span><span style="text-decoration: underline;">http://en.wikipedia.org/wiki/One-time_pad</span></span><span aria-hidden="true" class="ui-icon ui-icon-extlink ui-icon-inline" title="Links to an external site."></span><span class="screenreader-only">&nbsp;(Links to an external site.)</span></a></p>
<p>The following definitions will be important:</p>
<p><strong>Plaintext</strong> is the term for the information that you wish to encrypt and protect. It is human readable.</p>
<p><strong>Ciphertext</strong> is the term for the plaintext after it has been encrypted by your programs. Ciphertext is not human-readable, and in fact cannot be cracked, if the OTP system is used correctly.</p>
<p>A <strong>Key</strong> is the random sequence of characters that will be used to convert Plaintext to Ciphertext, and back again. It must not be re-used, or else the encryption is in danger of being broken.</p>
<p>The following excerpt from this Wikipedia article was captured on 2/21/2015:</p>
<p><span style="color: #993300;">“Suppose Alice wishes to send the message "HELLO" to Bob. Assume two pads of paper containing identical random sequences of letters were somehow previously produced and securely issued to both. Alice chooses the appropriate unused page from the pad. The way to do this is normally arranged for in advance, as for instance 'use the 12th sheet on 1 May', or 'use the next available sheet for the next message'.</span></p>
<p><span style="color: #993300;">The material on the selected sheet is the key for this message. Each letter from the pad will be combined in a predetermined way with one letter of the message. (It is common, but not required, to assign each letter a numerical value, e.g., "A" is 0, "B" is 1, and so on.)</span></p>
<p><span style="color: #993300;">In this example, the technique is to combine the key and the message using modular addition. The numerical values of corresponding message and key letters are <em>added</em> together, modulo 26. So, if key material begins with "XMCKL" and the message is "HELLO", then the coding would be done as follows:</span></p>
<div>
<pre><span style="color:;">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; H&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; E&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; L&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; L&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; O&nbsp; message
&nbsp;&nbsp; 7 (H)&nbsp;&nbsp; 4 (E)&nbsp; 11 (L)&nbsp; 11 (L)&nbsp; 14 (O) message
+ 23 (X)&nbsp; 12 (M)&nbsp;&nbsp; 2 (C)&nbsp; 10 (K)&nbsp; 11 (L) key
= 30&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; 16&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; 13&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; 21&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; 25&nbsp;&nbsp;&nbsp;&nbsp; message + key
=&nbsp; 4 (E)&nbsp; 16 (Q)&nbsp; 13 (N)&nbsp; 21 (V)&nbsp; 25 (Z) message + key (mod 26)
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; E&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Q&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; N&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; V&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Z&nbsp; → ciphertext</span></pre>
</div>
<p><span style="color: #993300;">If a number is larger than 26, then the remainder, after <em>subtraction</em> of 26, is taken [as the result]. This simply means that if the computations "go past" Z, the sequence starts again at A.</span></p>
<p><span style="color: #993300;">The ciphertext to be sent to Bob is thus "EQNVZ". Bob uses the matching key page and the same process, but in reverse, to obtain the plaintext. Here the key is <em>subtracted</em> from the ciphertext, again using modular arithmetic:</span></p>
<div>
<pre><span style="color: #993300;">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; E&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Q&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; N&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; V&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Z&nbsp; ciphertext
&nbsp;&nbsp;&nbsp; 4 (E)&nbsp; 16 (Q)&nbsp; 13 (N)&nbsp; 21 (V)&nbsp; 25 (Z) ciphertext
-&nbsp; 23 (X)&nbsp; 12 (M)&nbsp;&nbsp; 2 (C)&nbsp; 10 (K)&nbsp; 11 (L) key
= -19&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; 4&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; 11&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; 11&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; 14&nbsp;&nbsp;&nbsp;&nbsp; ciphertext – key
=&nbsp;&nbsp; 7 (H)&nbsp;&nbsp; 4 (E)&nbsp; 11 (L)&nbsp; 11 (L)&nbsp; 14 (O) ciphertext – key (mod 26)
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; H&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; E&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; L&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; L&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; O&nbsp; → message</span></pre>
</div>
<p><span style="color: #993300;">Similar to the above, if a number is negative then 26 is <em>added</em> to make the number zero or higher.</span></p>
<p><span style="color: #993300;">Thus Bob recovers Alice's plaintext, the message "HELLO". Both Alice and Bob destroy the key sheet immediately after use, thus preventing reuse and an attack against the cipher.”</span></p>
<p>Your program will encrypt and decrypt plaintext into ciphertext, using a key, in exactly the same fashion as above, except it will be using modulo 27 operations: your 27 characters are the 26 capital letters, and the space character ( ). All 27 characters will be encrypted and decrypted as above.</p>
<p>To do this, you will be creating five small programs in C. Two of these will function like "daemons" (but aren't actually daemons), and will be accessed using network sockets. Two will use the daemons to perform work, and the last is a standalone utility.</p>
<p>Your programs must use the network calls we've discussed in class (<span style="font-family: Courier New;">send()</span>, <span style="font-family: Courier New;">recv()</span>, <span style="font-family: Courier New;">socket()</span>, <span style="font-family: Courier New;">bind()</span>, <span style="font-family: Courier New;">listen()</span>, &amp; <span style="font-family: Courier New;">accept()</span>) to send and receive sequences of bytes for the purposes of encryption and decryption by the appropriate daemons. The whole point is to use the network, even though for testing purposes we're using the same machine: if you just <span style="font-family: Courier New;">open()</span> the datafiles from the server without using the network calls, you'll receive 0 points on the assignment.</p>
<p>Here are the specifications of the five programs:</p>
<p><span style="font-size: 12pt;"><strong><span style="font-family: Courier New;">otp_enc_d:</span></strong></span> This program will run in the background as a daemon. Upon execution, <span style="font-family: Courier New;">otp_enc_d</span> must output an error if it cannot be run due to a network error, such as the ports being unavailable. Its function is to perform the actual encoding, as described above in the Wikipedia quote. This program will listen on a particular port/socket, assigned when it is first ran (see syntax below). When a connection is made, <span style="font-family: Courier New;">otp_enc_d</span> must call <span style="font-family: Courier New;">accept()</span> to generate the socket used for actual communication, and then use a separate process to handle the rest of the transaction (see below), which will occur on the newly accepted socket.</p>
<p>This&nbsp;child process of <span style="font-family: Courier New;">otp_enc_d</span>&nbsp;must first check to make sure it is communicating with <span style="font-family: Courier New;">otp_enc</span> (see <span style="font-family: Courier New;">otp_enc</span>, below). After verifying that the connection to <span style="font-family: Courier New;">otp_enc_d</span> is coming from <span style="font-family: Courier New;">otp_enc</span>, then this child receives from <span style="font-family: Courier New;">otp_enc</span> plaintext and a key via the communication socket (not the original listen socket). The <span style="font-family: Courier New;">otp_enc_d</span> child will then write back the ciphertext to the <span style="font-family: Courier New;">otp_enc</span> process that it is connected to via the same communication socket. Note that the key passed in must be at least as big as the plaintext.</p>
<p>Your version of <span style="font-family: Courier New;">otp_enc_d</span> must support up to five <em>concurrent</em> socket connections running at the same time; this is different than the number of processes that could queue up on your listening socket (which is specified in the second parameter of the <span style="font-family: Courier New;">listen()</span> call). Again, only in the child process will the actual encryption take place, and the ciphertext be written back: the original server daemon process continues listening for new connections, not encrypting data.</p>
<p>In terms of creating that child process as described above, you may either create with <span style="font-family: Courier New;">fork()</span> a <em>new</em> process every time a connection is made, <em>or</em> set up a pool of five processes at the beginning of the program, before connections are allowed, to handle your encryption tasks. As above, your system must be able to do five separate encryptions at once, using either method you choose.</p>
<p>Use this syntax for <span style="font-family: Courier New;">otp_enc_d</span>:</p>
<pre>otp_enc_d <em>listening_port</em></pre>
<p><em>listening_port</em> is the port that <span style="font-family: Courier New;">otp_enc_d</span> should listen on. You will always start <span style="font-family: Courier New;">otp_enc_d</span> in the background, as follows (the port 57171 is just an example; yours should be able to use any port):</p>
<pre>$ otp_enc_d 57171 &amp;</pre>
<p>In all error situations, this&nbsp;program must output errors to stderr as appropriate (see grading script below for details), but should not crash or otherwise exit, unless the errors happen when the program is starting up (i.e. are part of the networking start up protocols like bind()). If given bad input, once running, <span style="font-family: Courier New;">otp_enc_d</span> should recognize the bad input, report an error to stderr, and continue to run. Generally speaking, though, this daemon shouldn't receive bad input, since that should be discovered and handled in the client first. All error text must be output to <em>stderr</em>.</p>
<p>This program, and the other 3 network programs, should use "localhost" as the target IP address/host. This makes them use the actual computer they all share as the target for the networking connections.</p>
<p><span style="font-size: 12pt;"><strong><span style="font-family: Courier New;">otp_enc:</span></strong></span> This program connects to <span style="font-family: Courier New;">otp_enc_d</span>, and asks it to perform a one-time pad style encryption as detailed above. By itself, <span style="font-family: Courier New;">otp_enc</span> doesn’t do the encryption - <span style="font-family: Courier New;">otp_enc_d</span> does. The syntax of <span style="font-family: Courier New;">otp_enc</span> is as follows:</p>
<pre>otp_enc <em>plaintext key port</em></pre>
<p>In this syntax, <em><span style="font-family: Courier New;">plaintext</span></em> is the name of a file in the current directory that contains the plaintext you wish to encrypt. Similarly, <em><span style="font-family: Courier New;">key</span></em> contains the encryption key you wish to use to encrypt the text. Finally, <em><span style="font-family: Courier New;">port</span></em> is the port that <span style="font-family: Courier New;">otp_enc</span> should attempt to connect to <span style="font-family: Courier New;">otp_enc_d</span> on.</p>
<p>When <span style="font-family: Courier New;">otp_enc</span> receives the ciphertext back from <span style="font-family: Courier New;">otp_enc_d</span>, it should output it to <em>stdout</em>. Thus, <span style="font-family: Courier New;">otp_enc</span> can be launched in any of the following methods, and should send its output appropriately:</p>
<pre>$ otp_enc myplaintext mykey 57171<br>$ otp_enc myplaintext mykey 57171 &gt; myciphertext<br>$ otp_enc myplaintext mykey 57171 &gt; myciphertext &amp;</pre>
<p>If <span style="font-family: Courier New;">otp_enc</span> receives key or plaintext files with ANY bad characters in them, or the key file is shorter than the plaintext, then it should&nbsp;terminate, send appropriate error text to stderr, and set the exit value to 1.</p>
<p><span style="font-family: Courier New;">otp_enc</span> should NOT be able to connect to <span style="font-family: Courier New;">otp_dec_d</span>, even if it tries to connect on the correct port - you'll need to have the programs reject each other. If this happens, <span style="font-family: Courier New;">otp_enc</span> should report the rejection to stderr and then terminate itself. In more detail: if&nbsp;<span style="font-family: Courier New;">otp_enc</span>&nbsp;cannot connect to the <span style="font-family: Courier New;">otp_enc_d</span>&nbsp;server, for any reason (including that it has accidentally tried to connect to the&nbsp;<span style="font-family: Courier New;">otp_dec_d</span>&nbsp;server), it should report this error to stderr with the attempted port, and set the exit value to 2. Otherwise, upon successfully running and terminating, <span style="font-family: Courier New;">otp_enc</span>&nbsp;should set the exit value to 0.</p>
<p>Again, any and all error text must be output to stderr&nbsp;(not into the plaintext or ciphertext files).</p>
<p><span style="font-size: 12pt;"><strong><span style="font-family: Courier New;">otp_dec_d:</span></strong></span> This program performs exactly like <span style="font-family: Courier New;">otp_enc_d</span>, in syntax and usage. In this case, however, <span style="font-family: Courier New;">otp_dec_d</span> will decrypt ciphertext it is given, using the passed-in ciphertext and key. Thus, it returns plaintext again to<span style="font-family: Courier New;"> otp_dec</span>.</p>
<p><span style="font-size: 12pt;"><strong><span style="font-family: Courier New;">otp_dec:</span></strong></span> Similarly, this program will connect to <span style="font-family: Courier New;">otp_dec_d</span> and will ask it to decrypt ciphertext using a passed-in ciphertext and key, and otherwise performs exactly like&nbsp;<span style="font-family: Courier New;">otp_enc</span>, and must be runnable in the same three ways. <span style="font-family: Courier New;">otp_dec</span> should NOT be able to connect to <span style="font-family: Courier New;">otp_enc_d</span>, even if it tries to connect on the correct port - you'll need to have the programs reject each other, as described in <span style="font-family: Courier New;">otp_enc</span>.</p>
<p><span style="font-size: 12pt;"><strong><span style="font-family: Courier New;">keygen:</span></strong></span> This program creates a key file of specified length. The characters in the file generated will be any of the 27 allowed characters, generated using the standard UNIX randomization methods. Do not create spaces every five characters, as has been historically done. Note that you specifically do not have to do any fancy random number generation: we’re not looking for cryptographically secure random number generation! <span style="font-family: Courier New;">rand()</span> is just fine. The last character keygen outputs should be a newline.&nbsp;All error text must be output to <em>stderr</em>, if any.</p>
<p>The syntax for <span style="font-family: Courier New;">keygen</span> is as follows:</p>
<pre>keygen <em>keylength</em></pre>
<p>Where <em><span style="font-family: Courier New;">keylength</span></em> is the length of the key file in characters. <span style="font-family: Courier New;">keygen</span> outputs to stdout. Here is an example run, which redirects stdout to a key file of 256 characters called “mykey” (note that mykey is 257 characters long because of the newline):</p>
<pre>$ keygen 256 &gt; mykey</pre>
<p><strong>Files and Scripts</strong></p>
<p>You are provided with 5 plaintext files to use (<span class="instructure_file_holder link_holder instructure_file_link_holder"><a class="" title="plaintext1" href="/courses/1738955/files/76095699/download?wrap=1" target="" data-api-endpoint="https://oregonstate.instructure.com/api/v1/courses/1738955/files/76095699" data-api-returntype="File" data-id="76095699">one</a><a class="file_download_btn" role="button" download="" style="margin-inline-start: 5px; text-decoration: none;" href="https://canvas.oregonstate.edu/courses/1738955/files/76095699/download?download_frd=1" data-id="76095699">
            <span class="screenreader-only">
              Download one
            </span>
          </a></span>, <span class="instructure_file_holder link_holder instructure_file_link_holder"><a class="" title="plaintext2" href="/courses/1738955/files/76095692/download?wrap=1" target="" data-api-endpoint="https://oregonstate.instructure.com/api/v1/courses/1738955/files/76095692" data-api-returntype="File" data-id="76095692">two</a><a class="file_download_btn" role="button" download="" style="margin-inline-start: 5px; text-decoration: none;" href="https://canvas.oregonstate.edu/courses/1738955/files/76095692/download?download_frd=1" data-id="76095692">
            <span class="screenreader-only">
              Download two
            </span>
          </a></span>, <span class="instructure_file_holder link_holder instructure_file_link_holder"><a class="" title="plaintext3" href="/courses/1738955/files/76095717/download?wrap=1" target="" data-api-endpoint="https://oregonstate.instructure.com/api/v1/courses/1738955/files/76095717" data-api-returntype="File" data-id="76095717">three</a><a class="file_download_btn" role="button" download="" style="margin-inline-start: 5px; text-decoration: none;" href="https://canvas.oregonstate.edu/courses/1738955/files/76095717/download?download_frd=1" data-id="76095717">
            <span class="screenreader-only">
              Download three
            </span>
          </a></span>, <span class="instructure_file_holder link_holder instructure_file_link_holder"><a class="" title="plaintext4" href="/courses/1738955/files/76095711/download?wrap=1" target="" data-api-endpoint="https://oregonstate.instructure.com/api/v1/courses/1738955/files/76095711" data-api-returntype="File" data-id="76095711">four</a><a class="file_download_btn" role="button" download="" style="margin-inline-start: 5px; text-decoration: none;" href="https://canvas.oregonstate.edu/courses/1738955/files/76095711/download?download_frd=1" data-id="76095711">
            <span class="screenreader-only">
              Download four
            </span>
          </a></span>, <span class="instructure_file_holder link_holder instructure_file_link_holder"><a class="" title="plaintext5" href="/courses/1738955/files/76095687/download?wrap=1" target="" data-api-endpoint="https://oregonstate.instructure.com/api/v1/courses/1738955/files/76095687" data-api-returntype="File" data-id="76095687">five</a><a class="file_download_btn" role="button" download="" style="margin-inline-start: 5px; text-decoration: none;" href="https://canvas.oregonstate.edu/courses/1738955/files/76095687/download?download_frd=1" data-id="76095687">
            <span class="screenreader-only">
              Download five
            </span>
          </a></span>). The grading will use these specific files; do not feel like you have to create others.</p>
<p>You are also provided with a grading script ("<span class="instructure_file_holder link_holder instructure_file_link_holder"><a class="" title="p4gradingscript" href="/courses/1738955/files/76095712/download?wrap=1" target="" data-api-endpoint="https://oregonstate.instructure.com/api/v1/courses/1738955/files/76095712" data-api-returntype="File" data-id="76095712">p4gradingscript</a><a class="file_download_btn" role="button" download="" style="margin-inline-start: 5px; text-decoration: none;" href="https://canvas.oregonstate.edu/courses/1738955/files/76095712/download?download_frd=1" data-id="76095712">
            <span class="screenreader-only">
              Download p4gradingscript
            </span>
          </a></span>")&nbsp;that you can run to test your software. If it passes the tests in the script, and has sufficient commenting, it will receive full points (see below). EVERY TIME you run this script, change the port numbers you use! Otherwise, because UNIX may not let go of your ports immediately, your successive runs may fail!</p>
<p>Finally, you will be required to write a compilation script (see below) that compiles all five of your programs, allowing you to use whatever C code and methods you desire. This will ease grading. Note that only C will be allowed, no C++ or any other language (Python, Perl, awk, etc.).</p>
<p><strong>Example</strong></p>
<p>Here is an example of usage, if you were testing your code from the command line:</p>
<pre>$ cat plaintext1
THE RED GOOSE FLIES AT MIDNIGHT STOP<br>$ otp_enc_d 57171 &amp;<br>$ otp_dec_d 57172 &amp;<br>$ keygen 10<br>EONHQCKQ I<br>$ keygen 10 &gt; mykey<br>$ cat mykey<br>VAONWOYVXP
$ keygen 10 &gt; myshortkey<br>$ otp_enc plaintext1 myshortkey 57171 &gt; ciphertext1 <br>Error: key ‘myshortkey’ is too short
$ echo $?
1<br>$ keygen 1024 &gt; mykey<br>$ otp_enc plaintext1 mykey 57171 &gt; ciphertext1
$ cat ciphertext1<br>WANAWTRLFTH RAAQGZSOHCTYS JDBEGYZQDQ<br>$ keygen 1024 &gt; mykey2<br>$ otp_dec ciphertext1 mykey 57172 &gt; plaintext1_a<br>$ otp_dec ciphertext1 mykey2 57172 &gt; plaintext1_b<br>$ cat plaintext1_a<br>THE RED GOOSE FLIES AT MIDNIGHT STOP<br>$ cat plaintext1_b<br>WSXFHCJAEISWQRNO L ZAGDIAUAL IGGTKBW<br>$ cmp plaintext1 plaintext1_a<br>$ echo $?
0
$ cmp plaintext1 plaintext1_b<br>plaintext1 plaintext1_b differ: byte 1, line 1
$ echo $?
1<br>$ otp_enc plaintext5 mykey 57171<br>otp_enc error: input contains bad characters<br>$ echo $?<br>1
$ otp_enc plaintext3 mykey 57172<br>Error: could not contact otp_enc_d on port 57172<br>$ echo $?
2
$</pre>
<p><strong>Compilation Script</strong></p>
<p>You must also write a short bash shell script called “compileall” that merely compiles your five programs. For example, the first two lines might be:</p>
<pre>#!/bin/bash<br>gcc -o otp_enc_d otp_enc_d.c<br>…</pre>
<p>This script will be used to compile your software, and must successfully run on our class server. The compilation must create all five programs, in the same directory as “compileall”, for immediate use by the grading script, which is named “p4gradingscript”.</p>
<h2>Hints</h2>
<p><strong>Where to Start</strong></p>
<p>First, write <span style="font-family: Courier New;">keygen</span> - it's simple and fun! Then, use our sample network programs <span class="instructure_file_holder link_holder instructure_file_link_holder"><a class="file_preview_link" title="client.c" href="/courses/1738955/files/76095697/download?wrap=1" target="" data-api-endpoint="https://oregonstate.instructure.com/api/v1/courses/1738955/files/76095697" data-api-returntype="File" aria-expanded="false" aria-controls="preview_1" data-id="76095697">client.c</a><a class="file_download_btn" role="button" download="" style="margin-inline-start: 5px; text-decoration: none;" href="https://canvas.oregonstate.edu/courses/1738955/files/76095697/download?download_frd=1" data-id="76095697">
            <span class="screenreader-only">
              Download client.c
            </span>
          </a><div role="region" class="preview_container" id="preview_1" style="display: none;"></div></span> and <span class="instructure_file_holder link_holder instructure_file_link_holder"><a class="file_preview_link" title="server.c" href="/courses/1738955/files/76095685/download?wrap=1" target="" data-api-endpoint="https://oregonstate.instructure.com/api/v1/courses/1738955/files/76095685" data-api-returntype="File" aria-expanded="false" aria-controls="preview_2" data-id="76095685">server.c</a><a class="file_download_btn" role="button" download="" style="margin-inline-start: 5px; text-decoration: none;" href="https://canvas.oregonstate.edu/courses/1738955/files/76095685/download?download_frd=1" data-id="76095685">
            <span class="screenreader-only">
              Download server.c
            </span>
          </a><div role="region" class="preview_container" id="preview_2" style="display: none;"></div></span> (you don't have to cite your use of them) to implement <span style="font-family: Courier New;">otp_enc</span> and <span style="font-family: Courier New;">otp_enc_d</span>. Once they are functional, copy them and begin work on <span style="font-family: Courier New;">otp_dec</span> and <span style="font-family: Courier New;">otp_dec_d</span>.</p>
<p>If you have questions about what your programs needs to be able to do, just examine the grading script. Your programs have to deal with exactly what's in there: no more, no less. :)</p>
<p><strong>Sending Data</strong></p>
<p>Recall that when sending data, not all of the data may be written with just one call to send() or write(). This occurs because of network interruptions, server load, and other factors. You'll need to carefully watch the number of characters read and/or written, as appropriate. If the number returned is less than what you intended, you'll need to restart the process from where it stopped. This means you'll need to wrap a loop around the send/receive routines to ensure they finish their job before continuing.</p>
<p>If you try to send too much data at once, the server will likely break the transmission, as in the previous paragraph. Consider setting a maximum send size, breaking the transmission yourself every 1000 characters, say.</p>
<p>There are a few ways to handle knowing how much data you need to send in a given transmission. One way is to send an integer from client to server (or vice versa) first, informing the other side how much is coming. This relatively small integer is unlikely to be split and interrupted. Another way is to have the listening side looking for a termination character that it recognizes as the end of the transmission string. It could loop, for example, until it has seen that termination character.</p>
<p><strong>Concurrency Implications</strong></p>
<p>Remember that only one socket can be bound to a port at a time. Multiple incoming connections all queue up on the socket that has had <span style="font-family: Courier New;">listen()</span> called on it for that port. After each <span style="font-family: Courier New;">accept()</span> call is made, a new socket file descriptor is returned which is your server's handle to that TCP connection. The server can accept multiple incoming streams, and communicate with all of them, by continuing to call <span style="font-family: Courier New;">accept()</span>, generating a new socket file descriptor each time.</p>
<p><strong>About Newlines</strong></p>
<p>You are&nbsp;only supposed to accept the 26 letters of alphabet and the "space" character as valid for encrypting and decrypting. However, all of the plaintext input files end with a newline character, and all text files you generate must end in a newline character.</p>
<p>When one of your programs reads in an input file, strip off the newline. Then encrypt and decrypt the text string, again with no newline character. When you send the result to stdout, or save results into a file, you <em>must</em> tack a newline to the end, or your length will be off in the grading script. Note that the newline character affects the length of files as reported by the wc command! Try it!</p>
<p><strong>About Reusing Sockets</strong></p>
<p>In the p4gradingscript, you can select which ports to use: I recommend ports in the 50000+ range. However, UNIX doesn't immediately let go of the ports you use after your program finishes! I highly recommend that you frequently change and randomize the sockets you're using, to make sure you're not using sockets that someone else is playing with. In addition, to allow your program to continue to use the same port (your mileage may vary), read this:</p>
<p><a href="https://beej.us/guide/bgnet/html/multi/#setsockoptman" class="external" target="_blank" rel="noreferrer noopener"><span>https://beej.us/guide/bgnet/html/multi/#setsockoptman</span><span aria-hidden="true" class="ui-icon ui-icon-extlink ui-icon-inline" title="Links to an external site."></span><span class="screenreader-only">&nbsp;(Links to an external site.)</span></a></p>
<p>...and then play around with this command:</p>
<pre>setsockopt(sock_fd, SOL_SOCKET, SO_REUSEADDR, &amp;yes, sizeof(int));</pre>
<p><strong>Where to Develop</strong></p>
<p>I <span style="text-decoration: underline; color: #ff0000;"><em><strong>HIGHLY</strong></em></span> recommend that you develop this program directly on our class&nbsp;server! Doing so will prevent you from having problems transferring the program back and forth, which can cause compatibility issues. Do not use any other non-class server to develop these programs.</p>
<p>If you do see ^M characters all over your files, which come from copying a Windows-saved file onto a UNIX file system, try this command:</p>
<pre>$ dos2unix bustedFile</pre>
<h2>What to&nbsp;Turn In and When</h2>
<p>Please submit a single zip file of your program code, which may be in as many different files as you want. Inside that zip file, include the following files:</p>
<ol>
<li>
<p>All of your program code</p>
</li>
<li>
<p>The compilation script named "compileall"</p>
</li>
<li>
<p>All five plaintext# files, numbered 1 through 5</p>
</li>
<li>
<p>A copy of the grading script named "p4gradingscript"</p>
</li>
</ol>
<p>Failing to submit one of the required pieces results in an 8-point deduction, while we attempt to contact you to submit what's missing. Your submission date &amp; time is whenever you send in the missing piece.</p>
<p>As our Syllabus says,&nbsp;please&nbsp;be aware that neither the&nbsp;Instructor nor the TA(s)&nbsp;are alerted to comments added to the text boxes in Canvas that are alongside your assignment submissions, and they may not be seen. No notifications (email or otherwise) are sent out&nbsp;when these&nbsp;comments are added, so we aren't aware that you have added content! If you need to make a meta-comment about this assignment, please include it in&nbsp;a README file&nbsp;in your .zip file, or email the person directly who will be grading it (see the&nbsp;<a title="Home Page" href="/courses/1738955/pages/home-page" data-api-endpoint="https://oregonstate.instructure.com/api/v1/courses/1738955/pages/home-page" data-api-returntype="Page">Home</a>&nbsp;page for grading responsibilities).</p>
<p>The due date given below is the last minute that this can be turned in for full credit. The "available until" date is NOT the due date, but instead closes off submissions for this assignment automatically once 48 hours past the due date has been reached, in accordance with our <a class="" title="Course Syllabus" href="/courses/1738955/assignments/syllabus#grading" target="">Syllabus Grading policies</a>.</p>
<h2>Grading</h2>
<p>In a bash prompt, on our class server, the graders will run the "compileall" script, and will then run the "p4gradingscript". They will make a reasonable effort to make your code compile, but if it doesn’t compile, you’ll receive a zero on this assignment.</p>
<p>If it compiles, it will have the "p4gradingscript" script ran against it for final grading, in this manner, in a bash prompt on&nbsp;our class server, where you fill in numbers for PORT1 and PORT2:</p>
<pre>$ ./p4gradingscript PORT1&nbsp;PORT2&nbsp;&gt; mytestresults 2&gt;&amp;1</pre>
<p>The graders will change the ports around each time they run the grading script, to make sure the ports used aren't in-use. Points will be assigned according to this grading script.</p>
<p>150 points are available in the grading script, while the final 10 points will be based on your style, readability, and commenting. Comment well, often, and verbosely (at least every five lines, say): we want to see that you are telling us WHY you are doing things, in addition to telling us WHAT you are doing.</p>
<p>The TAs will use this exact set of instructions: <span class="instructure_file_holder link_holder instructure_file_link_holder ally-file-link-holder"><a class="file_preview_link" title="Program4 Grading.pdf" href="/courses/1738955/files/76095683/download?wrap=1" target="" data-api-endpoint="https://oregonstate.instructure.com/api/v1/courses/1738955/files/76095683" data-api-returntype="File" aria-expanded="false" aria-controls="preview_3" data-id="76095683">Program4 Grading.pdf</a><div class="inline-block ally-enhancement ally-user-content-dropdown">
    <a href="#" role="button" tabindex="0" class="al-trigger" aria-haspopup="true">
        <span class="screenreader-only">Actions</span>
    </a>
    <ul class="al-options ui-menu ui-widget ui-widget-content ui-corner-all ui-popup ui-kyle-menu use-css-transitions-for-show-hide" id="ui-id-1" role="menu" tabindex="0" aria-hidden="true" aria-expanded="false" style="display: none; top: 6574.57px; left: 399px;" aria-activedescendant="ui-id-3"><span class="ui-menu-carat" style="left: 93.1667px; top: 131px; transform: rotateX(180deg);"><span></span></span>
        <li class="ui-menu-item" role="presentation"><a href="#" class="ally_trigger_inline_preview ui-corner-all" data-preview-id="preview_3" id="ui-id-2" tabindex="-1" role="menuitem">Preview</a></li>
        <li class="ui-menu-item" role="presentation"><a href="https://canvas.oregonstate.edu/courses/1738955/files/76095683/download?download_frd=1" data-id="76095683" id="ui-id-3" class="ui-corner-all" tabindex="-1" role="menuitem">Download</a></li>
        <li class="ui-menu-item" role="presentation"><a href="#" class="ally-accessible-versions ui-corner-all" data-id="76095683" id="ui-id-4" tabindex="-1" role="menuitem">Alternative formats</a></li>
    </ul>
</div><div role="region" class="preview_container" id="preview_3" style="display: none;"></div></span>&nbsp;to grade your submission.</p>