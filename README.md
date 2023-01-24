
# Projet Chat

Projet composé d'un client et d'un serveur, développé en C++, sur la base des sockets POSIX.

## Protocole de communication

Ce protocole est à respecter pour toute communication entre un client et le serveur.

| Préfixe à la chaîne de caractère | Signification |
| --- | --- |
| `/p <pseudo>`	| Envoie son pseudo au serveur |
| `/?*` | Mise à jour complète de tous les utilisateurs : trame au format `pseudo1 ip1;pseudo2 ip2;pseudo3 ip3;` |
| `?+ <pseudo>:<ip>` | Ajoute cet utilisateur à la liste des connexions |
| `/?- <pseudo>:<ip>` | Supprime cet utilisateur de la liste des connexions |
| `/b` | Envoie un message *broadcast*, un message à tous les utilisateurs connectés |
| `/m <pseudo>:<ip>;message` | Envoie un message à une personne |
| `/x <pseudo>:<ip>` | Déconnexion du client |
| `/t` | Token de présence (envoyé toutes les secondes). Le serveur renvoie l'heure. |  
