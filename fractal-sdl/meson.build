exe_name = 'fractal-sdl'

args = ['-s', 'USE_SDL=2']
executable(exe_name, 'main.c', name_suffix:'js', c_args:args,  link_args:args)

# Configure index.html
conf_data = configuration_data()
conf_data.set('exe_name', exe_name)
configure_file(input : 'index.html.in',
               output : 'index.html',
               configuration : conf_data)
