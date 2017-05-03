exe_name = 'hello-world'
executable(exe_name, 'main.c', name_suffix:'js')

# Configure index.html
conf_data = configuration_data()
conf_data.set('exe_name', exe_name)
configure_file(input : 'index.html.in',
               output : 'index.html',
               configuration : conf_data)
