# Guardfile

notification :tmux,
  display_message: true,
  timeout: 5,
  default_message_format: '%s >> %s',
  line_separator: ' > ',
  color_location: 'status-left-bg'

notification :terminal_notifier

guard :shell do
  watch("CMakeLists.txt") do
    cmake = `mkdir -p build && cd build && cmake -DTEST=ON ..`
    puts cmake
    n cmake.each_line.to_a[-1][3..-1], "CMake", ($? == 0 ? :success : :failed)
  end

  watch(%r{^(include|src|spec|test)\/(.+)\.(c(pp)?|h)$|^main\.c$}) do |m|
    build = `cd build && make`
    puts build
    if $? != 0
        n "Build Failed", 'make', :failed
        next
    end

    unit = `build/runUnit`
    puts unit
    if $? != 0
        n unit.each_line.to_a[-2], 'CppUTest', :failed
        next
    end

    spec = `build/runSpec`
    puts spec
    if $? != 0
        n spec.each_line.to_a[-1], 'igloo', :failed
        next
    end

    n "All of Build, Unit, Spec succeeded.", "Integrity", :success
  end
end
