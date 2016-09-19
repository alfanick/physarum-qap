#!/usr/bin/env ruby

require 'fileutils'

cmds = []

Dir['data/qapdatsol/*.dat'].sort.each do |input|
  name = File.basename(input, '.dat')
  group = name.split(/\d/)[0]

  FileUtils.mkdir_p("results/multiple/#{group}")

  n = name.delete('^0-9').to_i

  time = [n * 10, 900].min

  cmds << "sleep I; ./bin/physarum --data data/qapdatsol/#{name}.dat --time=#{time} --population=100 --sample=300 --e_explore=0.001 --e_crawl=0.01 -x > results/multiple/#{group}/#{name}.I.sln"
end

10.times do |i|
  cmds.each do |cmd|
    puts cmd.gsub('I', i.to_s)
  end
end
