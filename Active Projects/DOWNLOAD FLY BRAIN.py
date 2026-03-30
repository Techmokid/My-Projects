# put into commandprompt: "%USERPROFILE%\venvs\fafbseg\Scripts\activate"





from fafbseg import flywire

flywire.set_chunkedgraph_secret("PASTE_YOUR_TOKEN_HERE")
flywire.set_default_dataset("public")

#neurons = flywire.get_connectivity(1)
