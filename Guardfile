# Guardfile

notification :tmux,
  display_message: true,
  timeout: 5, # in seconds
  default_message_format: '%s >> %s',
  # the first %s will show the title, the second the message
  # Alternately you can also configure *success_message_format*,
  # *pending_message_format*, *failed_message_format*
  line_separator: ' > ', # since we are single line we need a separator
  color_location: 'status-left-bg' # to customize which tmux element will change color

notification :terminal_notifier

guard :shell do
  watch("CMakeLists.txt") do
    cmake = `mkdir -p build && cd build && cmake .. -Dtest=ON`.each_line.to_a[-1]
    puts cmake
    n cmake[3..-1], "CMake", ($? == 0 ? :success : :failed)
  end

  watch(%r{^(src|spec|test)\/(.+)\.c(pp)?$|^main\.c$}) do |m|
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
