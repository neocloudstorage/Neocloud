
public class RegisterInDBAction {
	private String username;
	private String password; 
	public String getPassword() {
		return password;
	}

	public void setPassword(String password) {
		this.password = password;
	}

	public String getUsername() {
		return username;
	}
 
	public void setUsername(String username) {
		this.username = username;
	}
	
	public String execute(){
		if(username.length()==0|password.length()==0|!username.contentEquals(password)){
		return "FAILURE";
		}
		return "SUCCESS";
	}
}
