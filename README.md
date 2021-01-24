# Morse

Les fichiers translation et build construisent à proprement parler la traduction.
Les fichiers write et read permettent respectivement d'écrire dans un fichier wave et d'en lire un.

Il faut se placer dans le sous-dossier cppfile pour compiler. Le makefile est un peu rudimentaire mais make run permet de compiler.

Pour une raison inconnue, mettre un espace dans le texte interrompt la transcription du texte vers le morse.
Normalement, le programme devrait simplement ignorer l'espace (comme tous les caractères qu'il ne connaît pas,
d'ailleurs c'est les cas pour les virgules et les apostrophes par exemple) mais ce n'est pas le cas. C'est comme
si quand on mettait un espace dans un char* depuis le terminal, il le considérait comme le caractère nul (qui, lui, 
interrompt la transcription) ?!

Le sens morse vers texte est un peu plus long parce que je passe lorsque nécessaire par une transformation de Fourier. On pourrait optimiser en calculant les intégrales par des trapèzes plutôt que des rectangles par exemple ce qui permettrait de réduire le pas.