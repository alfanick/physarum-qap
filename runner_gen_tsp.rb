#!/usr/bin/env ruby

require 'fileutils'

cmds = []

Dir['data/tsplib/{bays29,berlin52,bier127,pr152,pr226,st70,swiss42,eil101,d198,ch130,ch150}.in'].sort.each do |input|
  name = File.basename(input, '.in')
  group = name.split(/\d/)[0]

  FileUtils.mkdir_p("results/tsp/multiple/#{group}")

  n = name.delete('^0-9').to_i

  time = [n * 12, 900].min

  cmds << "sleep I; ./bin/physarum-tsp --data data/tsplib/#{name}.in --time=#{time} --population=10 --sample=1000000 --e_explore=0.01 --e_initial=100.0 -x -q 1.25 -a 0.8 > results/tsp/multiple/#{group}/#{name}.I.sln"
end

10.times do |i|
  cmds.each do |cmd|
    puts cmd.gsub('I', i.to_s)
  end
end
