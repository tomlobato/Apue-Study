#!/usr/bin/ruby

out = ""

File.open(ARGV[0]) {|f| out = f.read}

out.gsub!(/\/\*.*?\*\//m,'')
out.gsub!(/\/\/.*$/,'')
out.gsub!(/(\n\s*\n)+/m, "\n\n")
out.gsub!(/\n{3,}/m, "\n\n")

puts out

