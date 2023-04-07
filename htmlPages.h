/*
*	brief: HTML de paginas
*	author: Luca Agostini
*	date: 10/4/2019
*/

const char MAIN_page[] PROGMEM = R"=====(
<h1 style="color: #5e9ca0;">Men&uacute; de control</h1>
<hr />
<h2 style="color: #2e6c80;">Tareas:</h2>
<p>&nbsp;</p>
<ol style="list-style: none; font-size: 14px; line-height: 32px; font-weight: bold;">
<li style="clear: both;"><form action="/reset" method="POST">
<p><img style="float: left;" src="https://img.icons8.com/ultraviolet/40/000000/synchronize.png" alt="interactive connection" width="35" />&nbsp;<input type="submit" value="Resetear dispositivo externo" /></p>
</form></li>
<li style="clear: both;"><form action="/passwordChange" method="POST">
<p><img style="float: left;" src="https://img.icons8.com/ultraviolet/40/000000/private2.png" alt="interactive connection" width="35" />&nbsp;<input type="submit" value="Cambiar contrase&ntilde;a" /></p>
</form></li>
<li style="clear: both;"><form action="/" method="GET"><img style="float: left;" src="https://img.icons8.com/ultraviolet/40/000000/circled-left.png" alt="interactive connection" width="35" />&nbsp;<input type="submit" value="Salir" /></form></li>
<li style="clear: both;"></li>
</ol>
<p>&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp;</p>
<hr />
<p>&nbsp;</p>
)=====";

const char ROOT_page[] PROGMEM = R"=====( 
<h1 style="color: #5e9ca0;">Login de usuario</h1>
<p>&nbsp;</p>
<hr /><form action="/login" method="POST">
<h4 style="color: #2e6c80;">&nbsp; <span style="color: #000000;">Usuario:&nbsp; &nbsp; &nbsp;&nbsp;</span>&nbsp;<input name="username" type="text" placeholder="Username" /></h4>
<h4>&nbsp; Contrase&ntilde;a:&nbsp;<input name="password" type="password" placeholder="Password" /></h4>
<p>&nbsp;</p>
<p>&nbsp; &nbsp;<input type="submit" value="Login" /></p>
</form><hr />
<p>&nbsp;</p>
)=====";

const char PASSWORDCH_page[] PROGMEM = R"=====( 
<h1 style="color: #5e9ca0; text-align: left;">Cambiar contrase&ntilde;a</h1>
<form action="/changePasswordAccept" method="POST">
<hr />
<h4>&nbsp; Contrase&ntilde;a actual:&nbsp;<input name="passwordOld" type="password" placeholder="Contrase&ntilde;a" /></h4>
<h4>&nbsp; Nueva contrase&ntilde;a:&nbsp;<input name="passwordNew1" type="password" placeholder="Nueva contrase&ntilde;a" /></h4>
<h4>&nbsp; Repetir nueva contrase&ntilde;a:&nbsp;<input name="passwordNew2" type="password" placeholder="Nueva contrase&ntilde;a" /></h4>
<p>&nbsp;</p>
<p><em>Nota: La contrase&ntilde;a no debe tener mas de 10 caracteres</em></p>
<hr />
<table style="height: 16px; width: 539px;">
<tbody>
<tr>
<td style="width: 314px;">&nbsp;<input type="reset" value="Nuevo"></td>
<td style="width: 213px; text-align: left;">&nbsp;&nbsp;<input type="submit" value="Aceptar"></td>
</tr>
</tbody>
</table>
</form>
)=====";
