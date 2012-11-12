package view;

import java.io.BufferedInputStream;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.InputStream;
import java.util.concurrent.locks.ReentrantLock;

import model.Model;
import formatter.IFormatter;

public class Watcher implements Runnable, IAlgorithmController {

	private IController control;
	private IFormatter form;
	private Model model;
	private InputStream input;
	private java.util.concurrent.locks.Lock lock;
	
	private int time = 1000;
	private boolean state = true;
	private BufferedInputStream bis  =null;
	

	public Watcher(IController c, IFormatter form, InputStream str){
		this.control = c;
		this.form = form;
		this.input = str;
		this.lock = new ReentrantLock();  
		bis = new BufferedInputStream(input);
	}

	@Override
	public void run() {
		try {
			while(true){
				int cnt;
				boolean aval; 
				lock.lock();
				cnt = time;
				aval = state;
				lock.unlock();
				//System.out.println("waiting for entry...");
				//if(false)throw new InterruptedException();
				//do{
				
				Thread.sleep(cnt);
				while(!aval){
					Thread.sleep(cnt);
					lock.lock();
					cnt = time;
					aval = state;
					lock.unlock();
				}
				//}while(bis.available()<=0);
				synchronized (control.GetModel()) {
					this.model = form.getNextStep(bis, control.GetModel());
					control.Refresh(model);
				}
			}
		} catch (InterruptedException e) {
			e.printStackTrace();
		}finally{
			//lock.unlock();
		}
	}

	@Override
	public void start() {
		lock.lock();
		state = true;
		lock.unlock();
	}

	@Override
	public void stop() {
		lock.lock();
		state = false;
		lock.unlock();
	}

	@Override
	public void setTimeInterval(int miliseconds) {
		lock.lock();
		this.time = miliseconds;
		lock.unlock();
	}

	@Override
	public void setFilename(String filename) {
		try {
			if(this.bis != null)
				bis.close();
			this.bis = new BufferedInputStream(new FileInputStream(filename));
		} catch (FileNotFoundException e) {
			e.printStackTrace();
		} catch (IOException e) {
			e.printStackTrace();
		}
	}
	
	
	
}
