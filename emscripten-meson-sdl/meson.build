exe_name = 'sdl'

add_global_arguments(['-s', 'USE_SDL=2'], language : ['c','cpp'])
add_global_link_arguments(['-s', 'USE_SDL=2'], language : ['c','cpp'])

executable(exe_name, 'main.c', name_suffix:'js')

# Configure index.html
conf_data = configuration_data()
conf_data.set('js_name', exe_name + '.js')
configure_file(input : 'index.html.in',
               output : 'index.html',
               configuration : conf_data)
